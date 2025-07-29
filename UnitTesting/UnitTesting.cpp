#include <nlopt.hpp>
#include <cmath>
#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <exprtk.hpp>

// Struct with all the necessary data about the system of non-linear equations
struct exprtkData
{
    std::vector<std::string> equations;
    std::vector<std::vector<double>> exponents;
    std::vector<std::string> varNames;
};

/*struct tempLoop
{

};

double temps_objective_function(const std::vector<double>& t, std::vector<double>& grad, void* f_data) {

    // Import the info struct from the void* data
    tempLoop* Info = static_cast<tempLoop*>(f_data);

    // Copy the t vector, so as to work with it
    double T = t[0];

    double enthError = 0.0;
    double computedEnth = 0.0;

    // All theoretical kp container
    std::vector<double> allKpTheor;

    // For every selected kp expression, calculate theoretical kp, and store it
    for (size_t r = 0; r < howManyKpExp; ++r) {

        // Unpack the info tuple from the kp map for the selected kp expression
        const auto& [kpTuples, exponents] = kpVectors.at(allSelectedKpExp[r]);

        // Find the matching Kp coefficient set for the current temperature
        auto it = find_if(kpTuples.begin(), kpTuples.end(), [T](const auto& entry) {
            double Tmin = std::get<0>(entry);
            double Tmax = std::get<1>(entry);
            return T >= Tmin && T <= Tmax;
            });

        // A-E data to append
        const std::vector<double>& kpcoeffs = std::get<2>(*it);

        // Unpack coefficients for clarity (append previous data)
        A = kpcoeffs[0];
        B = kpcoeffs[1];
        C = kpcoeffs[2];
        D = kpcoeffs[3];
        E = kpcoeffs[4];

        // Calculate theoretical kp
        double kptheor = pow(10, A * pow(T, 4) + B * pow(T, 3) + C * pow(T, 2) + D * T + E);

        allKpTheor.push_back(kptheor);

    }

    // Calculate experimental kp and compare it to theoretical kp
    std::vector<double> solutionsVector = expKpHandler(reactantsCompounds, reactantsCoeff, productsCompounds, productsCoeff, allSelectedKpExp, pressure, allKpTheor);

    // Get the vector of doubles fully evaluated, for the right enthalpy
    std::vector<double> evaluatedProductsCoefficients = simpleEvalHandler(symbolicProductsCoeffs, solutionsVector);

    // Calculate right enthalpy of formation
    double rightEnth = 0.0;
    for (int k = 0; k < productsCompounds.size(); ++k) {
        rightEnth += evaluatedProductsCoefficients[k] * enthalpies[productsCompounds[k]];
    }

    // Calculate the "target" enthalpy of formation
    double targetEnth = leftEnth - rightEnth;

    // Iterate through the products, looking up their Cp coefficients, calculating enthalpies
    for (size_t j = 0; j < productsCompounds.size(); ++j) {

        const auto& names = productsCompounds[j];
        const auto& cpdata = compoundVectors[names];

        // Find the Cp coefficients valid for temperature t
        auto it = std::find_if(cpdata.begin(), cpdata.end(), [T](const auto& entry) {
            return T >= entry.first.first && T <= entry.first.second;
            });

        const std::vector<double>& coeffs = it->second;

        // Calculate "computed enthalpy" (Cp shomate equations)
        computedEnth += (evaluatedProductsCoefficients[j] * (intCp(coeffs, T/1000) - intCp(coeffs, 0.298))) * 1000.0;
    }

    return computedEnth*computedEnth + targetEnth*targetEnth;

}
*/

double objective_function(const std::vector<double>& x, std::vector<double>& grad, void* f_data) {

    // Import the info struct from the void* data
    exprtkData* Info = static_cast<exprtkData*>(f_data);

    // Copy the x vector, so as to work with it
    std::vector<double> a = x;

    std::cout << a[0] << " " << a[1] << " " << a[2] << "\n";

    // Create the vector holding all expressions, the parser and the symbol table
    std::vector<exprtk::expression<double>> expressions;
    exprtk::parser<double> parser;
    exprtk::symbol_table<double> symbol_table;

    // Add all the present variables to the symbol table, and their respective value (given by the nelder-mead algorithm)
    for (size_t i = 0; i < Info->varNames.size(); ++i) {
        symbol_table.add_variable(Info->varNames[i], a[i]);
    }
    symbol_table.add_constants(); // And add constants too

    // Check all values guessed by nelder mead, if any of them is <=0 discard the solution by giving a huge penalty of 1e10
    for (size_t j = 0; j < x.size(); ++j) {
        if (x[j] <= 0) return 1e10;
    }

    // Take every equation in the struct and make it an exprtk expression: register the symbols, parse it and add it to the expressions vector
    for (auto& eq : Info->equations) {
        exprtk::expression<double> e;
        e.register_symbol_table(symbol_table);
        parser.compile(eq, e);
        expressions.push_back(e);
    }

    // Set the sum of the squares, which nlopt minimizes
    double sum_sq = 0.0;

    // Evaluate the expressions and get their squares, add them and return the sum for nlopt
    for (auto& e : expressions) {
        double val = e.value();
        sum_sq += val * val;
    }

    return sum_sq;  // return the sum of squares
}

int main() {

    std::vector<std::string> nonLinearEquations = { "4 - 3*X - 2*Z", "2 - X - 2*Y", "8672 - (sqrt(Y) * (Z^(3/2)) / X) * (34.022 / (X + Y + Z ))" };

    exprtkData Info = {
        nonLinearEquations,
        {{1,0.5,0.5},{1,1,0.5}},
        {"X","Y","Z"}
    };


    auto start = std::chrono::system_clock::now();
    nlopt::opt opt(nlopt::LN_PRAXIS, Info.varNames.size()); // Run nelder mead with as many variables as present

    // Lower bounds, one for each present variable
    std::vector<double> lb(Info.varNames.size(), 0.0);
    opt.set_lower_bounds(lb);
    //std::vector<double> ub(Info.varNames.size(), 10.0);
    //opt.set_upper_bounds(ub);

    // Objective function
    opt.set_min_objective(objective_function, static_cast<void*>(&Info));
    opt.set_stopval(1e-9);

    std::vector<double> x(Info.varNames.size(), 1.0); // initial guess
    double minf;

    nlopt::result result = opt.optimize(x, minf);

    auto end = std::chrono::system_clock::now();

    std::cout << Info.equations[0] << "\n" << Info.equations[1] << "\n" << Info.equations[2] << "\n" /* << Info.equations[3] << "\n"*/;
    //std::cout << "a = " << x[0] << ", b = " << x[1] << "\n";
    std::cout << "Computing time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << "ns" << "\n";
    std::cout << "Solution: x = " << x[0]
        << ", y = " << x[1]
        << ", z = " << x[2]
        /* << ", w = " << x[3]*/ << "\n"
        << "Sum of sq residuals: " << minf << "\n";
        //<< std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << "ns";

    return 0;
}