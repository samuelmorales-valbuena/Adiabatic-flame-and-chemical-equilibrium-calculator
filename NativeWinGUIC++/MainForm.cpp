#include "MainForm.h"
#include "HelpForm.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept> 
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <limits>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <unordered_map>
#include <optional>
#include <numeric>
#include <cctype>
#include <variant>
#include <exprtk.hpp>
#include <regex>
#include <msclr\marshal_cppstd.h>
#include <nlopt.hpp>

using namespace System;


//
// MAP SECTION --------------------------------------------------------------------------------------------------
//

// Map of compounds to their atom count
static std::map<std::string, std::map<std::string, int>> atom_counts = {
    {"O2",   {{"O", 2}}},
    {"H",    {{"H", 1}}},
    {"H2",   {{"H", 2}}},
    {"OH",   {{"O", 1}, {"H", 1}}},
    {"H2O",  {{"H", 2}, {"O", 1}}},
    {"N",    {{"N", 1}}},
    {"N2",   {{"N", 2}}},
    {"NO",   {{"N", 1}, {"O", 1}}},
    {"CO",   {{"C", 1}, {"O", 1}}},
    {"CO2",  {{"C", 1}, {"O", 2}}},
    {"CH4",  {{"C", 1}, {"H", 4}}},
    {"C2H2", {{"C", 2}, {"H", 2}}},
    {"Cl",   {{"Cl", 1}}},
    {"Cl2",  {{"Cl", 2}}},
    {"HCl",  {{"H", 1}, {"Cl", 1}}},
    {"NH",   {{"N", 1}, {"H", 1}}},
    {"NH3",  {{"N", 1}, {"H", 3}}},
    {"CH2",  {{"C", 1}, {"H", 2}}},
    {"NO2",  {{"N", 1}, {"O", 2}}},
    {"N2H4", {{"N", 2}, {"H", 4}}}
};

// Map of cpmpounds to their Enthalpy of formation
static std::map<std::string, double> enthalpies = {
    {"O", 249180},
    {"O2", 0},
    {"H", 218000},
    {"H2", 0},
    {"OH", 38990},
    {"H2O", -241818},
    {"N", 472680},
    {"N2", 0},
    {"NO", 90290},
    {"CO", -110530},
    {"CO2", -393520},
    {"CH4", -74850},
    {"C2H2", 226700},
    {"Cl", 121300},
    {"Cl2", 0},
    {"HCl", -92310},
    {"NH", 376560},
    {"NH3", -45940},
    {"CH2", 386390},
    {"NO2", 33100},
    {"N2H4", 95400}
};

// Map of compounds to their Shomate coefficient vectors with temperature ranges
static std::map<std::string, std::vector<std::pair<std::pair<double, double>, std::vector<double>>>> compoundVectors = {
    // O2 data
    {"O2", {
        {{100, 700}, {31.32234, -20.23531, 57.86644, -36.50624, -0.007374, -8.903471, 246.7945, 0}},
        {{700, 2000}, {30.03235, 8.772972, -3.988133, 0.788313, -0.741599, -11.32468, 236.1663, 0}},
        {{2000, 6000}, {20.91111, 10.72071, -2.020498, 0.146449, 9.245722, 5.337651, 237.6185, 0}}
    }},

    // H data
    {"H", {
        {{298, 6000}, {20.78603, 0.0000000004850638, -0.0000000001582916, 0.00000000001525102, 0.00000000003196347, 211.802, 139.8711, 217.9994}}
    }},

    // H2 data
    {"H2", {
        {{298, 1000}, {33.066178, -11.363417, 11.432816, -2.772874, -0.158558, -9.980797, 172.707974, 0}},
        {{1000, 2500}, {18.563083, 12.257357, -2.859786, 0.268238, 1.97799, -1.147438, 156.288133, 0}},
        {{2500, 6000}, {43.41356, -4.293079, 1.272428, -0.096876, -20.533862, -38.515158, 162.081354, 0}}
    }},

    // OH data
    {"OH", {
        {{298, 1300}, {32.27768, -11.36291, 13.60545, -3.846486, -0.001335, 29.75113, 225.5783, 38.98706}},
        {{1300, 6000}, {28.74701, 4.714489, -0.814725, 0.054748, -2.747829, 26.41439, 214.1166, 38.98706}}
    }},

    // H2O data
    {"H2O", {
        {{500, 1700}, {30.092, 6.832514, 6.793435, -2.53448, 0.082139, -250.881, 223.3967, -241.8264}},
        {{1700, 6000}, {41.96426, 8.622053, -1.49978, 0.098119, -11.15764, -272.1797, 219.7809, -241.8264}}
    }},

    // N data
    {"N", {
        {{298, 6000}, {21.13581, -0.388842, 0.043545, 0.024685, -0.025678, 466.311, 178.8263, 472.6832}}
    }},

    // N2 data
    {"N2", {
        {{100, 500}, {28.98641, 1.853978, -9.647459, 16.63537, 0.000117, -8.671914, 226.4168, 0}},
        {{500, 2000}, {19.50583, 19.88705, -8.598535, 1.369784, 0.527601, -4.935202, 212.39, 0}},
        {{2000, 6000}, {35.51872, 1.128728, -0.196103, 0.014662, -4.55376, -18.97091, 224.981, 0}}
    }},

    // NO data
    {"NO", {
        {{298, 1200}, {23.83491, 12.58878, -1.139011, -1.497459, 0.214194, 83.35783, 237.1219, 90.29114}},
        {{1200, 6000}, {35.99169, 0.95717, -0.148032, 0.009974, -3.004088, 73.10787, 246.1619, 90.29114}}
    }},

    // CO data
    {"CO", {
        {{298, 1300}, {25.56759, 6.09613, 4.054656, -2.671301, 0.131021, -118.0089, 227.3665, -110.5271}},
        {{1300, 6000}, {35.1507, 1.300095, -0.205921, 0.01355, -3.28278, -127.8375, 231.712, -110.5271}}
    }},

    // CO2 data
    {"CO2", {
        {{298, 1200}, {24.99735, 55.18696, -33.69137, 7.948387, -0.136638, -403.6075, 228.2431, -393.5224}},
        {{1200, 6000}, {58.16639, 2.720074, -0.492289, 0.038844, -6.447293, -425.9186, 263.6125, -393.5224}}
    }},

    // CH4 data
    {"CH4", {
        {{298, 1300}, {-0.703029, 108.4773, -42.52157, 5.862788, 0.678565, -76.84376, 158.7163, -74.8731}},
        {{1300, 6000}, {85.81217, 11.26467, -2.114146, 0.13819, -26.42221, -153.5327, 224.4143, -74.8731}}
    }},

    // C2H2 data
    {"C2H2", {
        {{298, 1100}, {40.68697, 40.73279, -16.1784, 3.669741, -0.658411, 210.7067, 235.0052, 226.7314}},
        {{1100, 6000}, {67.47244, 11.7511, -2.02147, 0.136195, -9.806418, 185.455, 253.5337, 226.7314}}
    }},

    // Cl data
    {"Cl", {
        {{298, 600}, {13.38298, 42.33999, -64.74656, 32.99532, 0.063319, 116.1491, 171.7038, 121.3021}},
        {{600, 6000}, {23.26597, -1.555939, 0.34691, -0.025961, 0.153212, 114.6604, 193.8882, 121.3021}}
    }},

    // Cl2 data
    {"Cl2", {
        {{298, 1000}, {33.0506, 12.2294, -12.0651, 4.38533, -0.159494, -10.8348, 259.029, 0}},
        {{1000, 3000}, {42.6773, -5.00957, 1.904621, -0.165641, -2.09848, -17.2898, 269.84, 0}},
        {{3000, 6000}, {-42.5535, 41.6857, -7.12683, 0.387839, 101.144, 132.764, 264.786, 0}}
    }},

    // HCl data
    {"HCl", {
        {{298, 1200}, {32.12392, -13.45805, 19.86852, -6.853936, -0.049672, -101.6206, 228.6866, -92.31201}},
        {{1200, 6000}, {31.91923, 3.203184, -0.541539, 0.035925, -3.438525, -108.015, 218.2768, -92.31201}}
    }},

    // NH data
    {"NH", {
        {{298, 800}, {31.31766, -8.931544, 11.58629, -2.544099, -0.041861, 367.382, 221.0867, 376.5604}},
        {{800, 6000}, {28.0592, 5.10084, -0.767827, 0.056843, -1.05472, 366.0623, 211.8351, 376.5604}}
    }},

    // NH3 data
    {"NH3", {
        {{298, 1400}, {19.99563, 49.77119, -15.37599, 1.921168, 0.189174, -53.30667, 203.8591, -45.89806}},
        {{1400, 6000}, {52.02427, 18.48801, -3.765128, 0.248541, -12.45799, -85.53895, 223.8022, -45.89806}}
    }},

    // CH2 data
    {"CH2", {
        {{298, 1400}, {31.96823, 6.783603, 12.5189, -5.696265, -0.031115, 376.3558, 229.915, 386.3924}},
        {{1400, 6000}, {51.55901, 3.876975, -0.649608, 0.037901, -10.72589, 350.6715, 232.3212, 386.3924}}
    }},

    // NO2 data
    {"NO2", {
        {{298, 1200}, {16.10857, 75.89525, -54.3874, 14.30777, 0.239423, 26.17464, 240.5386, 33.09502}},
        {{1200, 6000}, {56.82541, 0.738053, -0.144721, 0.009777, -5.459911, 2.846456, 290.5056, 33.09502}}
    }},

    // N2H4 data
    { "N2H4", {
        {{800, 2000}, {35.18240, 96.05260, -40.50130, 6.668070, -0.874233, 77.99150, 249.4250, 95.35340}},
        {{2000, 6000}, {121.4010, 4.816880, -0.763012, 0.043232, -40.78650, -11.38110, 305.3440, 95.35340}}

    }}
};

//Map of kp expressions
static std::map<std::vector<std::string>, std::tuple<std::vector<std::tuple<double, double, std::vector<double>>>, std::vector<double>>> kpVectors = {
    // kp1 data
    {{"O","O2"},{{
        {298,1500, {-5.25e-11, 2.30e-07, -3.78e-04, 2.89e-01, -9.84e+01}},
        {1500,5000,{0.00e+00, 1.86e-10, -2.35e-06, 1.05e-02, -1.64e+01}}
        }, {1, 1.0 / 2}
    }},
    // kp2 data
    {{"H","H2"},{{
        {298,1500,{-4.63e-11,2.20e-07,-3.33e-04,2.55e-01,-8.68e+01}},
        {1500,5000,{0.00e+00,1.65e-10,-2.08e-06,9.40e-03,1.46e+01}}
        }, {1, 1.0 / 2}

    }},
    // kp3 data
    {{"OH","O2","H2"},{{
        {298,1500,{-8.97e-12,3.93e-08,-6.46e-05,4.93e-02,-1.65e+01}},
        {1500,5000,{0.00e+00,3.04e-11,-3.81e-07,1.70e-03,-2.44e+00}}
        }, {1, 1.0 / 2, 1.0 / 2}

    }},
    // kp4 data
    {{"H2O","H2","O2"},{{
        {298,1500,{5.12e-11,-2.24e-07,3.69e-04,-2.82e-01,9.68e+01}},
        {1500,5000,{0.00e+00,-1.86e-10,2.34e-06,-1.05e-02,1.67e+01}}
        }, {1, 1.0, 1.0 / 2}

    }},
    // kp5 data
    {{"N","N2"},{{
        {298,1500,{-7.61e-11,3.33e-07,-5.47e-04,4.18e-01,-1.44e+02}},
        {1500,5000,{0.00e+00,2.68e-10,-3.38e-06,1.52e-02,-2.51e+01}}
        }, {1, 1.0 / 2}

    }},
    // kp6 data
    {{"NO","N2","O2"},{{
        {298,1500,{-1.92e-11,8.41e-08,-1.38e-04,1.06e-01,-3.64e+01}},
        {1500,5000,{0.00e+00,6.69e-11,-8.44e-07,3.80e-03,6.45e+00}}
        }, {1, 1.0, 1.0 / 2}

    }},

    //// kp8 data
    //{{"C", "C"},{{
    //    {{298,1500},{-1.53e-10,6.68e-07,-1.10e-03,8.40e-01,-2.87e+02}},
    //    {{1500,4000},{0.00e+00,8.97e-10,-9.66e-06,3.76e-02,-5.43e+01}}
    //    }, {1, 1, 1 / 2}

    //}},

    // kp9 data
    {{"CO","C","O2"},{{
        {298,1500,{2.34e-11,-1.02e-07,1.68e-04,-1.28e-01,4.98e+01}},
        {1500,4000,{0.00e+00,-1.37e-10,1.48e-06,-5.90e-03,1.44e+01}}
        }, {1, 1.0, 1.0 / 2}

    }},
    // kp10 data
    {{"CO2","C","O2"},{{
        {298,1500,{8.38e-11,-3.66e-07,6.02e-04,-4.60e-01,1.61e+02}},
        {1500,4000,{0.00e+00,-4.90e-10,5.27e-06,-2.06e-02,3.44e+01}}
        }, {1, 1.0, 1.0}

    }},
    // kp11 data
    {{"CH4","C","H2"},{{
        {298,1500,{1.51e-11,-6.63e-08,1.10e-04,-8.64e-02,2.65e+01}}
        }, {1, 1.0, 2.0}

    }},
    // kp12 data
    {{"C2H2","C","H2"},{{
        {298,1500,{-4.84e-11,2.12e-07,-3.48e-04,2.65e-01,-8.99e+01}}
        }, {1, 2.0, 1.0}

    }},
    // kp13 data
    {{"Cl","Cl2"},{{
        {298,1500,{-2.57e-11,1.12e-07,-1.85e-04,1.42e-01,-4.70e+01}}
        }, {1, 1.0 / 2}

    }},
    // kp14 data
    {{"HCl","H2","Cl2"},{{
        {298,1500,{1.96e-11,-8.56e-08,1.41e-04,-1.08e-01,3.83e+01}}
        }, {1, 1.0 / 2, 1.0 / 2}

    }},
    // kp15 data
    {{"NH","N2","H2"},{{
        {600,2000,{-8.73e-12,5.58e-08,-1.37e-04,1.62e-01,-9.04e+01}},
        {2000,4000,{0.00e+00,2.80e-10,-3.33e-06,1.46e-02,-2.69e+01}}
        }, {1, 1.0 / 2, 1.0 / 2}

    }},
    // kp16 data
    {{"NH3","N2","H2"},{{
        {600,2000,{1.08e-12,-7.02e-09,1.76e-05,-2.14e-02,6.48e+00}},
        {2000,4000,{0.00e+00,-4.46e-11,5.26e-07,-2.20e-03,-1.95e+00}}
        }, {1, 1.0 / 2, 3.0 / 2}

    }},
    // kp17 data
    {{"CH2","C","H2"},{{
        {600,2000,{-8.97e-12,5.73e-08,-1.41e-04,1.66e-01,-9.07e+01}},
        {2000,4000,{0.00e+00,2.83e-10,-3.37e-06,1.47e-02,-2.56e+01}}
        }, {1, 1.0, 1.0}

    }},
    // kp18 data
    {{"NO2","NO","O2"},{{
        {300,1600,{-9.84e-12,4.53e-08,-7.82e-05,6.24e-02,-1.92e+01}},
        {1600,3000,{0.00e+00,1.80e-10,-1.48e-06,4.50e-03,-2.45e+00}}
        }, {1, 1.0, 1.0 / 2}

    }},
    // kp19 data
    {{"NO","N2","O2"},{{
        {300,1800,{-1.03e-11,5.27e-08,-9.98e-05,8.66e-02,-3.32e+01}},
        {1800,5000,{0.00e+00,5.23e-11,-6.88e-07,3.30e-03,-5.87e+00}}
        }, {1, 1.0 / 2, 1.0 / 2}

    }}

};

//
// MAP SECTION --------------------------------------------------------------------------------------------------
//

//
// GENERAL UTILITY SECTION --------------------------------------------------------------------------------------------------
//

// Function to get the appropriate coefficient vector for a compound at a given temperature
std::vector<double> getCompoundVector(const std::string& compound, double temperature) {

    // Check if the compound exists in map
    if (compoundVectors.find(compound) == compoundVectors.end()) {
        throw std::runtime_error("Compound " + compound + " not found in database");
    }

    // Get the vector of temperature ranges and coefficients for this compound
    const auto& rangesandcoef = compoundVectors[compound];

    // Find the appropriate temperature range
    for (const auto& range : rangesandcoef) {
        double minTemp = range.first.first;
        double maxTemp = range.first.second;

        if (temperature >= minTemp && temperature <= maxTemp) {
            return range.second;
        }
    }

    throw std::runtime_error("Temperature " + std::to_string(temperature) + " out of range for compound " + compound);
}

// Function for the integrated expressions
double intCp(const std::vector<double>& coef,const double &rt) {
    return coef[0] * rt +
        coef[1] * pow(rt, 2) / 2 +
        coef[2] * pow(rt, 3) / 3 +
        coef[3] * pow(rt, 4) / 4 -
        coef[4] / rt;
}

// Function to find the overlapping temperature range for a list of compounds
std::pair<double, double> findOverlappingTemperatureRange(const std::vector<std::string>& compounds) {
    if (compounds.empty()) {
        throw std::runtime_error("No compounds provided");
    }

    double minTemp = -INFINITY;
    double maxTemp = INFINITY;

    // For each compound
    for (const auto& compound : compounds) {
        // Check if compound exists in database
        if (compoundVectors.find(compound) == compoundVectors.end()) {
            throw std::runtime_error("Compound " + compound + " not found in database");
        }

        // Find the min and max temperature across all ranges for this compound
        double compoundMinTemp = INFINITY;
        double compoundMaxTemp = -INFINITY;

        for (const auto& range : compoundVectors[compound]) {
            double rangeMinTemp = range.first.first;
            double rangeMaxTemp = range.first.second;

            compoundMinTemp = std::min(compoundMinTemp, rangeMinTemp);
            compoundMaxTemp = std::max(compoundMaxTemp, rangeMaxTemp);
        }

        // Update the overall min and max
        minTemp = std::max(minTemp, compoundMinTemp);
        maxTemp = std::min(maxTemp, compoundMaxTemp);
    }

    // Check if we have a valid overlapping range
    if (minTemp > maxTemp) {
        throw std::runtime_error("No overlapping temperature range exists for the specified compounds");
    }

    return { minTemp, maxTemp };
}

// Helper function to split a string by spaces
std::vector<std::string> splitKpString(const std::string& input) {
    std::vector<std::string> result;
    std::istringstream iss(input);
    std::string compound;

    while (iss >> compound) {
        std::string cleaned;
        for (char c : compound) {
            if (c != '=' && c != '+') {
                cleaned += c;
            }
        }
        if (!cleaned.empty()) {
            result.push_back(cleaned);
        }
    }

    return result;
}

//Chemical balance function
void splitChemicalTerms(const std::string& input, std::vector<double>& coefficients, std::vector<std::string>& compounds) {
    std::string filteredInput;

    // First, filter the input to only include allowed characters
    for (char c : input) {
        if (isalnum(c) || c == '.' || c == ' ') {
            filteredInput += c;
        }
    }

    std::istringstream iss(filteredInput);
    std::string term;

    while (iss >> term) {
        // Find where the coefficient ends and the compound begins
        size_t i = 0;
        while (i < term.length() && (isdigit(term[i]) || term[i] == '.')) {
            i++;
        }

        if (i > 0) {
            // There's a coefficient
            try {
                coefficients.push_back(stod(term.substr(0, i)));
                compounds.push_back(term.substr(i));
            }
            catch (...) {
                // If stod fails, treat as no coefficient
                coefficients.push_back(1.0);
                compounds.push_back(term);
            }
        }
        else {
            // No coefficient, default to 1
            coefficients.push_back(1.0);
            compounds.push_back(term);
        }
    }
}

//
// GENERAL UTILITY SECTION --------------------------------------------------------------------------------------------------
//

//
// COMPLETE COMBUSTION SECTION --------------------------------------------------------------------------------------------------
//

//Function to perform adiabatic flame temperature calculation for complete combustion
double completeCombustion(const std::string& reactantsInput, const std::string& productsInput, double tolerance = 0.000001) {

    std::vector<double> reactantsCoeff;
    std::vector<std::string> reactantsCompounds;
    std::vector<double> productsCoeff;
    std::vector<std::string> productsCompounds;

    splitChemicalTerms(reactantsInput, reactantsCoeff, reactantsCompounds);
    splitChemicalTerms(productsInput, productsCoeff, productsCompounds);

    std::vector<std::string> allCompounds;
    allCompounds.insert(allCompounds.end(), reactantsCompounds.begin(), reactantsCompounds.end());
    allCompounds.insert(allCompounds.end(), productsCompounds.begin(), productsCompounds.end());

    // Get valid temperature range
    std::pair<double, double> tempRange = findOverlappingTemperatureRange(allCompounds);
    double t_min = tempRange.first;
    double t_max = tempRange.second;
    double T0 = 298.15 / 1000.0;
    

    //The target enthalpy will be composed of the heats of formation, substracting the ones on the right (products) 
    //from the ones on the left (reactants)

    // Left enthalpy of formation
    double leftEnth = 0.0;
    for (int i = 0; i < reactantsCompounds.size(); ++i) {
        leftEnth += reactantsCoeff[i] * enthalpies[reactantsCompounds[i]];
    }

    // Right enthalpy
    double rightEnth = 0.0;
    for (int i = 0; i < productsCompounds.size(); ++i) {
        rightEnth += productsCoeff[i] * enthalpies[productsCompounds[i]];
    }

    // Target enthalpy
    double targetEnth = leftEnth - rightEnth;

    // Binary search setup
    double low = t_min;
    double high = t_max;
    double bestT = t_min;  // Fallback value
    double bestError = INFINITY;

    const int maxIterations = 500;  // Prevents infinite loops
    const double enthalpyTolerance = tolerance * abs(targetEnth);  // Allowable error


    // Main loop, temps
    for (int i = 0; i < maxIterations; ++i) {
        double mid = (low + high) / 2.0;
        double T = mid / 1000.0; //Shomate equations use K/1000
        double computedEnth = 0.0;

        // Iterate through the products, looking up their Cp coefficients, calculating enthalpies
        for (int j = 0; j < productsCompounds.size(); ++j) {
            const auto& names = productsCompounds[j];
            const auto& cpdata = compoundVectors[names];

            // Find the Cp coefficients valid for temperature t
            auto it = std::find_if(cpdata.begin(), cpdata.end(), [mid](const auto& entry) {
                return mid >= entry.first.first && mid <= entry.first.second;
                });

            const std::vector<double>& coeffs = it->second;

            computedEnth += (productsCoeff[j] * (intCp(coeffs, T) - intCp(coeffs, T0))) * 1000.0;
        }

        double enthError = computedEnth - targetEnth;

        // Track best solution
        if (abs(enthError) < bestError) {
            bestError = abs(enthError);
            bestT = mid;
        }

        // Check for convergence
        if (abs(enthError) <= enthalpyTolerance) {
            return mid;
        }

        // Update search bounds
        if (enthError > 0) {
            high = mid;  // Too hot, search lower half
        }
        else {
            low = mid;  // Too cold, search upper half
        }

        // Early exit if the range is too small
        if ((high - low) < 0.00000001) {  // 0.1 K precision
            break;
        }


    }

    return bestT;

}

//
// COMPLETE COMBUSTION SECTION --------------------------------------------------------------------------------------------------
//

//
// INCOMPLETE COMBUSTION SECTION --------------------------------------------------------------------------------------------------
//

// Helper function to remove repeated items, to sanitize repeated compounds in a several kp expression input scenario
std::vector<std::string> multipleKpExpSanitizer(const std::vector<std::vector<std::string>> &allSelectedKpExp) {
    
    std::vector<std::string> sanitizedVector;

    for (size_t i = 0; i < allSelectedKpExp.size(); ++i) {
        auto particularKpExp = allSelectedKpExp[i];
        for (size_t j = 0; j < particularKpExp.size(); ++j) {
            if (std::find(sanitizedVector.begin(), sanitizedVector.end(), particularKpExp[j]) == sanitizedVector.end()) {
                sanitizedVector.push_back(particularKpExp[j]);
            }
        }
    }

    return sanitizedVector;
}

// Function for incomplete combustion that returns mixed (numerical and symbolic) coefficients for the products as strings
std::vector<std::string> symbolicProductsCoeffHandler(const std::vector<std::string> &productsCompounds, const std::vector<double> &productsCoeff, const std::vector<std::vector<std::string>>& allSelectedKpExp) {
    
    // Setup symbolicProductsCoeff equal to productsCoeff
    std::vector<std::string> symbolicProductsCoeff;
    for (size_t i = 0; i < productsCoeff.size(); ++i) {
        symbolicProductsCoeff.push_back(std::to_string(productsCoeff[i]));
    }

    auto sanitizedKpComps = multipleKpExpSanitizer(allSelectedKpExp);

    // Replace coefficients of recombining products for variables in symbolicProductsCoeff
    for (size_t i = 0; i < productsCompounds.size(); ++i) {
        // If the product compound matches one of the recombining compounds,
        if (std::find(sanitizedKpComps.begin(), sanitizedKpComps.end(), productsCompounds[i]) != sanitizedKpComps.end()) {
            // Assign a symbolic variable (a, b, c...) based on the compound's position in selectedKpExp
            auto it = std::find(sanitizedKpComps.begin(), sanitizedKpComps.end(), productsCompounds[i]);
            size_t idx = std::distance(sanitizedKpComps.begin(), it);
            char var = 'a' + idx;
            symbolicProductsCoeff[i] = std::string(1, var); // Replace that item with "a", "b", etc. in the symbolic-numeric mixed coefficient vector
        }
    }
    return symbolicProductsCoeff;
}

// Function that converts elements in a string vector to doubles, replacing symbolic variables for their provided value
std::vector<double> simpleEvalHandler(const std::vector<std::string> &stringVector, const std::vector<double> &x) {
    std::vector<double> evaluatedDoubleVector;
    for (const auto& term : stringVector) {
        if (term.size() == 1 && std::isalpha(term[0])) {
            // Map letter to corresponding index in x
            size_t index = term[0] - 'a';
            if (index < x.size()) {
                evaluatedDoubleVector.push_back(x[index]);
            }
        }
        else {
            // Parse as number
            evaluatedDoubleVector.push_back(std::stod(term));
        }
    }
    return evaluatedDoubleVector;
}

 // Function that builds the atom balance equations, where every equation is a string in the returned string vector
std::vector<std::string> balanceEquationsHandler(const std::vector<std::string> &reactantsCompounds, const std::vector<double> &reactantsCoeff, const std::vector<std::string> &productsCompounds, const std::vector<double> &productsCoeff, const std::vector<std::vector<std::string>>& allSelectedKpExp) {
   
    std::vector<std::string> balanceEquations;

    // Setup symbolicProductsCoeff equal to productsCoeff
    std::vector<std::string> symbolicProductsCoeff = symbolicProductsCoeffHandler(productsCompounds, productsCoeff, allSelectedKpExp);

    // Setup of vector storing all the unique elements present in both sides
    std::set<std::string> uniqueElements;

    // Get the elements in reactants
    for (const auto& compound : reactantsCompounds) {
        for (const auto& [element, count] : atom_counts.at(compound)) {
            uniqueElements.insert(element);
        }
    }
    // Get the elements in products
    for (const auto& compound : productsCompounds) {
        for (const auto& [element, count] : atom_counts.at(compound)) {
            uniqueElements.insert(element);
        }
    }

    // For every unique element, 
    for (const std::string& element : uniqueElements) {
        std::string lhs = "";
        std::string rhs = "";

        // Reactants
        // For every compound in reactants, write the lhs of the equation, multiplying its coefficient with the current iteration element's count
        for (size_t i = 0; i < reactantsCompounds.size(); ++i) {
            const auto& compound = reactantsCompounds[i];
            int count = atom_counts[compound][element];
            if (count > 0) {
                lhs += (lhs.empty() ? "" : "+") + std::to_string(reactantsCoeff[i] * count);
            }
        }

        // Products (symbolic)
        // For every compound in products, write the rhs of the equation, multiplying its numeric coefficient or variable with the current iteration element's count
        for (size_t i = 0; i < productsCompounds.size(); ++i) {
            const auto& compound = productsCompounds[i];
            int count = atom_counts[compound][element];
            if (count > 0) {
                rhs += (rhs.empty() ? "" : "-") + symbolicProductsCoeff[i] + "*" + std::to_string(count);
            }
        }

        // Add the balance equation for the current element
        balanceEquations.push_back(lhs + "-" + rhs);
    }

    return balanceEquations;

}

// Function that builds the kptheor~kpexp non-linear equations, where every equation is a string in the returned string vector
std::vector<std::string> nonLinearEquationsBuilder(const std::vector<double>& allKpTheor, const std::vector<std::vector<std::string>>& allSelectedKpExp, const std::vector<std::string> &orderedProductCompounds, const std::vector<std::string> &orderedProductCoefficients, const double &pressure, const std::vector<double> &deltn, const std::vector<std::vector<double>> &expKpExponentsVector) {
    // Output vector
    std::vector<std::string> nonLinearEquations;

    // Experimental kp expressions vector
    std::vector<std::string> expKpExpressions(allSelectedKpExp.size());

    // Vector that stores the indexes for variable-to-compound correlation
    std::vector<std::vector<int>> distances(allSelectedKpExp.size());

    // String with the sum of all product variable coefficients
    std::string varSum;
    for (size_t n = 0; n < orderedProductCoefficients.size(); ++n) {
        varSum += (varSum.empty() ? "" : "+") + orderedProductCoefficients[n];
    }

    // Build the experimental kp expression
    for (size_t j = 0; j < allSelectedKpExp.size(); ++j) {

        std::vector<std::string> unorderedCompNames = allSelectedKpExp[j];

        for (auto unordComp : unorderedCompNames){
            auto itx = find(orderedProductCompounds.begin(), orderedProductCompounds.end(), unordComp);
            distances[j].push_back(distance(orderedProductCompounds.begin(), itx));
        }

        expKpExpressions[j] = std::string("(") + "(" + "(" + "(" + orderedProductCoefficients[distances[j][1]] + ")" + "^" + "(" + std::to_string(expKpExponentsVector[j][1]) + ")" + ")" + "*" + "(" + "(" + orderedProductCoefficients[distances[j][2]] + ")" + "^" + "(" + std::to_string(expKpExponentsVector[j][2]) + ")" + ")" + ")" +"/" + "(" + orderedProductCoefficients[distances[j][0]] + ")" +")" + "*" + "(" + std::to_string(pressure) + "/" + "(" + varSum + ")" + ")" + "^" + "(" + std::to_string(deltn[j]) + ")";
    }

    // Build the non-linear equation
    for (size_t i = 0; i < allKpTheor.size(); ++i) {
        nonLinearEquations.push_back(std::to_string(1/allKpTheor[i]) + " - " + expKpExpressions[i]);
    }
    return nonLinearEquations;
}

struct exprtkData {
    std::vector<std::string> equations;
    std::vector<std::string> varNames;
};

double objective_function(const std::vector<double>& x, std::vector<double>& grad, void* f_data) {

    // Import the info struct from the void* data
    exprtkData* Info = static_cast<exprtkData*>(f_data);

    // Copy the x vector, so as to work with it
    std::vector<double> a = x;

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
        if (a[j] <= 0) return 1e10;
    }

    // Take every equation in the struct and make it an exprtk expression: register the symbols, parse it and add it to the expressions vector
    for (auto& eq : Info->equations) {
        exprtk::expression<double> e;
        e.register_symbol_table(symbol_table);
        parser.compile(eq, e);
        expressions.push_back(e);
    }

    //System::Windows::Forms::MessageBox::Show("Expressions: " + gcnew String (Info->equations[0].c_str()) + "\n" + gcnew String(Info->equations[1].c_str()) + "\n" + gcnew String(Info->equations[2].c_str()));

    // Set the sum of the squares, which nlopt minimizes
    double sum_sq = 0.0;

    // Evaluate the expressions and get their squares, add them and return the sum for nlopt
    for (auto& e : expressions) {
        double val = e.value();
        sum_sq += val * val;
    }

    //System::Windows::Forms::MessageBox::Show("a: " + a[0].ToString() + "\n" + "b: " + a[1].ToString() + "\n" + "c: " + a[2].ToString() + "\n" + "Sumsq: " + sum_sq.ToString());

    return sum_sq;  // return the sum of squares
}

struct EquationSide {
    double constant = 0.0;
    double coefficient = 0.0;
};

EquationSide parse_side(const std::string& expr, const std::string& variable) {
    EquationSide result;

    // Match number * variable OR variable * number
    std::regex term_regex(R"(([+-]?\s*\d*\.?\d+)\s*\*?\s*([a-zA-Z]+)|([a-zA-Z]+)\s*\*?\s*([+-]?\s*\d*\.?\d+)|([+-]?\s*\d*\.?\d+))");
    auto begin = std::sregex_iterator(expr.begin(), expr.end(), term_regex);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it) {
        std::string coeff_str;
        std::string var;

        if ((*it)[1].matched && (*it)[2].matched) {
            // Form: number * variable
            coeff_str = (*it)[1].str();
            var = (*it)[2].str();
        }
        else if ((*it)[3].matched && (*it)[4].matched) {
            // Form: variable * number
            coeff_str = (*it)[4].str();
            var = (*it)[3].str();
        }
        else if ((*it)[5].matched) {
            // Form: constant (number only)
            coeff_str = (*it)[5].str();
            var = "";
        }

        // Remove spaces
        coeff_str.erase(remove_if(coeff_str.begin(), coeff_str.end(), ::isspace), coeff_str.end());

        if (coeff_str.empty() || coeff_str == "+") coeff_str = "1";
        else if (coeff_str == "-") coeff_str = "-1";

        double coeff = std::stod(coeff_str);

        if (var == variable) {
            result.coefficient += coeff;
        }
        else {
            result.constant += coeff;
        }
    }

    return result;
}

double solve_linear_equation(const std::string& equation, const std::string& variable) {
    size_t eq_pos = equation.find('=');
    if (eq_pos == std::string::npos) System::Windows::Forms::MessageBox::Show("No = found");

    std::string lhs = equation.substr(0, eq_pos);
    std::string rhs = equation.substr(eq_pos + 1);

    EquationSide left = parse_side(lhs, variable);
    EquationSide right = parse_side(rhs, variable);

    double var_coeff = left.coefficient - right.coefficient;
    double const_diff = right.constant - left.constant;

    if (var_coeff == 0) System::Windows::Forms::MessageBox::Show("Infinite solutions");

    return (const_diff / var_coeff);
}

std::string evaluate_numeric_expressions(const std::string& input) {
    std::string result = input;
    std::regex numeric_mul(R"(([+-]?\d*\.?\d+)\s*\*\s*([+-]?\d*\.?\d+))");

    std::smatch match;
    while (std::regex_search(result, match, numeric_mul)) {
        double a = std::stod(match[1].str());
        double b = std::stod(match[2].str());
        double product = a * b;

        // Replace the match with the result
        std::ostringstream oss;
        oss.precision(10);  // Match format
        oss << std::fixed << product;

        result.replace(match.position(0), match.length(0), oss.str());
    }

    return result;
}

static std::vector<double> expKpHandler(const std::vector<std::string> &reactantsCompounds, const std::vector<double> &reactantsCoeff, const std::vector<std::string> &productsCompounds, const std::vector<double> &productsCoeff, const std::vector<std::vector<std::string>> &allSelectedKpExp, const double &pressure, const std::vector<double> &allKpTheor) {

    // Vector that stores every delta-n
    std::vector<double> deltaNVector;
    deltaNVector.clear(); // Clear it

    // Vector that stores the exp kp exponents
    std::vector<std::vector<double>> expKpExponentsVector;
    expKpExponentsVector.clear(); // Clear it

    // For every selected kp expression, extract the correct kp exponents, calculate delta-n and assign a tolerance to its respective theoretical kp
    for (size_t v = 0; v < allSelectedKpExp.size(); ++v) {

        // Unpack the info tuple from the kp map for the selected kp expression in the listbox
        const auto& [kpTuples, exponents] = kpVectors.at(allSelectedKpExp[v]);

        //Delta-n
        double deltaN = (exponents[1]) + (exponents[2]) - exponents[0];

        /**********************************************************************************/

        // Add delta-n
        deltaNVector.push_back(deltaN);

        // Add set of exp kp exponents
        expKpExponentsVector.push_back(exponents);

    }

    // Vector with all present variables, before cleaning them
    auto allPresentVarsVector = symbolicProductsCoeffHandler(productsCompounds, productsCoeff, allSelectedKpExp);

    // Cleaned vector with usable variables
    std::vector<std::string> usableVarsVector;

    // Take the usable variables for the equation system from allPresentVarsVector and put them in usableVarsVector
    for (auto &itm : allPresentVarsVector) {
        if (!std::all_of(itm.begin(), itm.end(), ::isdigit)) {
            usableVarsVector.push_back(itm);
        }
        else continue;
    }

    // Get the atom balance equations
    std::vector<std::string> balanceEquations = balanceEquationsHandler(reactantsCompounds, reactantsCoeff, productsCompounds, productsCoeff, allSelectedKpExp);

    // Get the kp nonlinear equations
    std::vector<std::string> nonLinearEquations = nonLinearEquationsBuilder(allKpTheor, allSelectedKpExp, productsCompounds, usableVarsVector, pressure, deltaNVector, expKpExponentsVector);

    //System::Windows::Forms::MessageBox::Show(gcnew String(balanceEquations[0].c_str()) + "\n" + gcnew String(balanceEquations[1].c_str()) + "\n" + gcnew String(nonLinearEquations[0].c_str()));

    std::vector<std::string> nonLinearSystem;
    nonLinearSystem.insert(std::end(nonLinearSystem), std::begin(balanceEquations), std::end(balanceEquations));
    nonLinearSystem.insert(std::end(nonLinearSystem), std::begin(nonLinearEquations), std::end(nonLinearEquations));

    //System::Windows::Forms::MessageBox::Show(gcnew String(nonLinearSystem[0].c_str()) + "\n" + gcnew String(nonLinearSystem[1].c_str()) + "\n" + gcnew String(nonLinearSystem[2].c_str()));

    // Fill the struct objects before importing to the objective_function
    exprtkData nelderMeadInfo{
        nonLinearSystem,
        usableVarsVector
    };

    // Run nelder mead with as many variables as present
    nlopt::opt opt(nlopt::LN_PRAXIS, nelderMeadInfo.varNames.size());

    // Lower bounds, one for each present variable
    std::vector<double> lb(nelderMeadInfo.varNames.size(), 0.0);
    opt.set_lower_bounds(lb);
    //std::vector<double> ub(nelderMeadInfo.varNames.size(), 10.0);
    //opt.set_upper_bounds(ub);

    // Objective function
    opt.set_min_objective(objective_function, static_cast<void*>(&nelderMeadInfo));
    opt.set_stopval(1e-12);

    std::vector<double> x(nelderMeadInfo.varNames.size(), 1.0); // initial guesses, vector is as big as there are variables
    double minf;

    nlopt::result result = opt.optimize(x, minf);

    //System::Windows::Forms::MessageBox::Show("Sum of sq: " + minf);

    return x;

}

struct tempLoop
{
    int howmanykpexp;
    std::vector<std::vector<std::string>> allselectedkpexp;
    std::vector<std::string> reacComp;
    std::vector<double> reacCoef;
    std::vector<std::string> prodComp;
    std::vector<double> prodCoef;
    double press;
    std::vector<std::string> symbprodcoef;
    double leftenth;
};


double temps_objective_function(const std::vector<double>& t, std::vector<double>& grad, void* f_data) {

    // Import the info struct from the void* data
    tempLoop* tempInfo = static_cast<tempLoop*>(f_data);

    // Copy the t vector, so as to work with it
    double T = t[0];

    double enthError = 0.0;
    double computedEnth = 0.0;
    double A = 0.0, B = 0.0, C = 0.0, D = 0.0, E = 0.0;

    // All theoretical kp container
    std::vector<double> allKpTheor;

    // For every selected kp expression, calculate theoretical kp, and store it
    for (size_t r = 0; r < tempInfo->howmanykpexp; ++r) {

        // Unpack the info tuple from the kp map for the selected kp expression
        const auto& [kpTuples, exponents] = kpVectors.at(tempInfo->allselectedkpexp[r]);

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
    std::vector<double> solutionsVector = expKpHandler(tempInfo->reacComp, tempInfo->reacCoef, tempInfo->prodComp, tempInfo->prodCoef, tempInfo->allselectedkpexp, tempInfo->press, allKpTheor);

    //System::Windows::Forms::MessageBox::Show("Solutions 1: " + solutionsVector[0] + " " + solutionsVector[1] + " " + solutionsVector[2]);

    // Get the vector of doubles fully evaluated, for the right enthalpy
    std::vector<double> evaluatedProductsCoefficients = simpleEvalHandler(tempInfo->symbprodcoef, solutionsVector);

    //System::Windows::Forms::MessageBox::Show("Solutions 1: " + solutionsVector[0] + " " + solutionsVector[1] + " " + solutionsVector[2] + "Solutions 2: " + evaluatedProductsCoefficients[0] + " " + evaluatedProductsCoefficients[1] + " " + evaluatedProductsCoefficients[2]);

    // Calculate right enthalpy of formation
    double rightEnth = 0.0;
    for (int k = 0; k < tempInfo->prodComp.size(); ++k) {
        rightEnth += evaluatedProductsCoefficients[k] * enthalpies[tempInfo->prodComp[k]];
    }

    // Calculate the "target" enthalpy of formation
    double targetEnth = tempInfo->leftenth - rightEnth;

    // Iterate through the products, looking up their Cp coefficients, calculating enthalpies
    for (size_t j = 0; j < tempInfo->prodComp.size(); ++j) {

        const auto& names = tempInfo->prodComp[j];
        const auto& cpdata = compoundVectors[names];

        // Find the Cp coefficients valid for temperature t
        auto it = std::find_if(cpdata.begin(), cpdata.end(), [T](const auto& entry) {
            return T >= entry.first.first && T <= entry.first.second;
            });

        const std::vector<double>& coeffs = it->second;

        // Calculate "computed enthalpy" (Cp shomate equations)
        computedEnth += (evaluatedProductsCoefficients[j] * (intCp(coeffs, (T / 1000.0)) - intCp(coeffs, 0.298))) * 1000.0;
        //System::Windows::Forms::MessageBox::Show("Computed enth: " + (computedEnth).ToString() + " - iteration # " + (j).ToString() + "\n"
        //+ (evaluatedProductsCoefficients[0]).ToString() + " - " + (evaluatedProductsCoefficients[1]).ToString() + " - " + (evaluatedProductsCoefficients[2]).ToString());
    }

    enthError = targetEnth - computedEnth;

    // Control Message
    /*System::Windows::Forms::MessageBox::Show("Temperarure: " + T.ToString() + "\n" + "a: " + (solutionsVector[0]).ToString() + "\n"
    + "b: " + (solutionsVector[1]).ToString() + "\n" + "c: " + (solutionsVector[2]).ToString() + "\n" + "Left Enthalpy: " + tempInfo->leftenth.ToString()
    + "\n" + "Right Enthalpy: " + rightEnth.ToString() + "\n" + "Target Enthalpy: " + targetEnth.ToString() + "\n" 
    + "Computed Enthalpy: " + computedEnth.ToString() + "\n" + "Enthalpy Error: " + enthError.ToString() + "\n"
    + "Theoretical Kp: " + (1/allKpTheor[0]).ToString() + "\n");*/

    //System::Windows::Forms::MessageBox::Show("Enth error: " + enthError);

    return enthError*enthError;

}

std::tuple<double, std::vector<double>> incompleteCombustion(const std::string& reactantsInput, const std::string& productsInput, const double &tolerance,const std::vector<std::string> &recombChecklist,const double &pressure) {
    
    // Setup coefficient and compound vectors for reactants and products
    std::vector<double> reactantsCoeff;
    std::vector<std::string> reactantsCompounds;
    std::vector<double> productsCoeff;
    std::vector<std::string> productsCompounds;

    // Process Input into respective vectors
    splitChemicalTerms(reactantsInput, reactantsCoeff, reactantsCompounds);
    splitChemicalTerms(productsInput, productsCoeff, productsCompounds);

    // Join all compounds together in a vector of strings
    std::vector<std::string> allCompounds;
    allCompounds.insert(allCompounds.end(), reactantsCompounds.begin(), reactantsCompounds.end());
    allCompounds.insert(allCompounds.end(), productsCompounds.begin(), productsCompounds.end());

    // Get valid temperature range for all compounds
    std::pair<double, double> tempRange = findOverlappingTemperatureRange(allCompounds);
    double t_min = tempRange.first;
    double t_max = tempRange.second;
    // Set standard temperature divided by 1000
    double T0 = 298.15 / 1000.0;

    // Vector to get the selected kp checklist items
    std::vector<std::vector<std::string>> allSelectedKpExp(recombChecklist.size());

    // Add every selected kp expression, formatted by the function
    for (size_t h = 0; h < recombChecklist.size(); ++h) {
        allSelectedKpExp[h] = splitKpString(recombChecklist[h]);
    }

    // Save how many were selected
    int howManyKpExp = allSelectedKpExp.size();


    // Binary TEMPERATURE search setup
    double low = t_min;
    double high = 4000;
    double bestT = t_min;  // Fallback value
    double bestError = INFINITY;

    const int maxIterations = 100;  // Prevents infinite loops

    // Calculate left enthalpy of formation
    double leftEnth = 0.0;
    for (int p = 0; p < reactantsCompounds.size(); ++p) {
        leftEnth += reactantsCoeff[p] * enthalpies[reactantsCompounds[p]];
    }

    // Create the mixed string vector of coefficients, later the symbolic ones will be replaced with results from the system of nl eqs
    std::vector<std::string> symbolicProductsCoeffs = symbolicProductsCoeffHandler(productsCompounds, productsCoeff, allSelectedKpExp);

    double A = 0.0, B = 0.0, C = 0.0, D = 0.0, E = 0.0;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    tempLoop tempLoopInfo{
        howManyKpExp,
        allSelectedKpExp,
        reactantsCompounds,
        reactantsCoeff,
        productsCompounds,
        productsCoeff,
        pressure,
        symbolicProductsCoeffs,
        leftEnth
    };

    /*nlopt::opt opt(nlopt::LN_NELDERMEAD, 1);

    //nlopt::opt set_local_optimizer(const nlopt::opt &LN_NELDERMEAD);

    //Set bounds
    opt.set_lower_bounds(1000);
    //double ub = completeCombustion(reactantsInput, productsInput, tolerance);
    opt.set_upper_bounds(4000);

    // Objective function
    opt.set_min_objective(temps_objective_function, static_cast<void*>(&tempLoopInfo));
    opt.set_stopval(1e-6);

    std::vector<double> t = {1900}; // initial guesses, vector is as big as there are variables
    double minf;

    nlopt::result result = opt.optimize(t, minf);

    System::Windows::Forms::MessageBox::Show("Error: " + minf);*/

    // MAIN LOOP - TEMPERATURE *****************************************************************************************************************

    for (int i = 0; i < maxIterations; ++i) {
        double mid = (low + high) / 2.0;
        double T = mid / 1000.0; //Shomate equations use K/1000
        double enthError = 0.0;
        double computedEnth = 0.0;

        //System::Windows::Forms::MessageBox::Show("Temperarure: " + mid.ToString());

        // All theoretical kp container
        std::vector<double> allKpTheor;

        // For every selected kp expression, calculate theoretical kp, and store it
        for (size_t r = 0; r < howManyKpExp; ++r) {

            // Unpack the info tuple from the kp map for the selected kp expression
            const auto& [kpTuples, exponents] = kpVectors.at(allSelectedKpExp[r]);

            // Find the matching Kp coefficient set for the current temperature
            auto it = find_if(kpTuples.begin(), kpTuples.end(), [mid](const auto& entry) {
                double Tmin = std::get<0>(entry);
                double Tmax = std::get<1>(entry);
                return mid >= Tmin && mid <= Tmax;
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
            double kptheor = pow(10, A * pow(mid, 4) + B * pow(mid, 3) + C * pow(mid, 2) + D * mid + E);

            allKpTheor.push_back(kptheor);

        }
        
        // Calculate experimental kp and compare it to theoretical kp
        std::vector<double> solutionsVector = expKpHandler(reactantsCompounds, reactantsCoeff, productsCompounds, productsCoeff, allSelectedKpExp, pressure, allKpTheor);

        //System::Windows::Forms::MessageBox::Show("Temperarure: " + mid.ToString() + "\n" + "a: " + (solutionsVector[0]).ToString() + "\n" + "b: " + (solutionsVector[1]).ToString() + "\n" + "c: " + (solutionsVector[2]).ToString() + "\n");

        // Get the vector of doubles fully evaluated, for the right enthalpy
        std::vector<double> evaluatedProductsCoefficients = simpleEvalHandler(symbolicProductsCoeffs, solutionsVector);

        // Calculate right enthalpy of formation
        double rightEnth = 0.0;
        for (int k = 0; k < productsCompounds.size(); ++k) {
            rightEnth += evaluatedProductsCoefficients[k] * enthalpies[productsCompounds[k]];
        }
        
        // Calculate the "target" enthalpy of formation
        double targetEnth = leftEnth - rightEnth;

        double enthalpyTolerance = tolerance * abs(targetEnth);  // Allowable enthalpy error

        // Iterate through the products, looking up their Cp coefficients, calculating enthalpies
        for (size_t j = 0; j < productsCompounds.size(); ++j) {
                
            const auto& names = productsCompounds[j];
            const auto& cpdata = compoundVectors[names];

            // Find the Cp coefficients valid for temperature t
            auto it = std::find_if(cpdata.begin(), cpdata.end(), [mid](const auto& entry) {
                return mid >= entry.first.first && mid <= entry.first.second;
            });

            const std::vector<double>& coeffs = it->second;

            //System::Windows::Forms::MessageBox::Show("Coefficients -" + "\n" +
            //    coeffs[0] + " " + coeffs[1] + " " + coeffs[2] + " " + coeffs[3] + " " + coeffs[4] + " " + "\n");

            // Calculate "computed enthalpy" (Cp shomate equations)
            computedEnth += (evaluatedProductsCoefficients[j] * (intCp(coeffs, T) - intCp(coeffs, T0))) * 1000.0;
            //System::Windows::Forms::MessageBox::Show("Computed enth: " + (computedEnth).ToString() + " - iteration # " + (j).ToString() + "\n"
            //+ (evaluatedProductsCoefficients[0]).ToString() + " - " + (evaluatedProductsCoefficients[1]).ToString() + " - " + (evaluatedProductsCoefficients[2]).ToString());
        }

        // Calculate enthalpy error
        enthError = targetEnth - computedEnth;

        // Control Message
        //System::Windows::Forms::MessageBox::Show("Temperarure: " + mid.ToString() + "\n" + "a: " + (solutionsVector[0]).ToString() + "\n" + "b: " + (solutionsVector[1]).ToString() + "\n" + "c: " + (solutionsVector[2]).ToString() + "\n" + "Left Enthalpy: " + leftEnth.ToString() + "\n" + "Right Enthalpy: " + rightEnth.ToString() + "\n"
        //+ "Target Enthalpy: " + targetEnth.ToString() + "\n" + "Computed Enthalpy: " + computedEnth.ToString() + "\n" + "Enthalpy Error: " + enthError.ToString() + "\n" 
        //+ "Theoretical Kp: " + allKpTheor[0].ToString() + "\n");

        // Track best solution
        if (abs(enthError) < bestError) {
             bestError = abs(enthError);
             bestT = mid;
        }

        // Check for convergence
        if (abs(enthError) <= enthalpyTolerance) {
            return { {mid}, {solutionsVector} };
        }

        // Early exit if the range is too small
        if ((high - low) < 0.0000000000001) {  // 1E-13 K precision
            System::Windows::Forms::MessageBox::Show("T ran out of precision");
            break;
        }

        // Update search bounds
        if (enthError < 0) {
            high = mid;  // Too hot, search lower half
        }
        else {
            low = mid;  // Too cold, search upper half
        }

    }

    return { {bestT}, {0}};
}

//
// INCOMPLETE COMBUSTION SECTION --------------------------------------------------------------------------------------------------
//

//
// EXTENDED INCOMPLETE COMBUSTION SECTION ------------------------------------------------------------------------------------------
//

/*static std::tuple<double, double, std::vector<double>, double, double, double> extendedExperimentalKpHandler(const std::vector<std::string>& reactantsCompounds, const std::vector<double>& reactantsCoeff, const std::vector<std::string>& productsCompounds, const std::vector<double>& productsCoeff, const std::vector<std::string>& selectedKpExp, const double& leftEnth, const double& pressure, const double& kptheor, const double& tolerance) {

    // Binary FRACTION search setup
    double lowx = 0;
    double highx = 1.0;
    double bestX = 0;  // Fallback value
    double bestXError = INFINITY;

    // Unpack the info tuple from the kp map for the selected kp expression in the listbox
    const auto& [kpTuples, exponents] = kpVectors.at(selectedKpExp);

    //Delta-n
    double deltn = accumulate(exponents.begin(), exponents.end(), 0.0);

    double kpTolerance = tolerance * abs(kptheor);  // Allowable enthalpy error

    // SECOND LOOP - KP

    for (int x = 0; x < 100; ++x) {


        double midx = (lowx + highx) / 2.0;
        double computedEnth = 0.0;
        double a = midx;
        double b = 0, c = 0;
        double kpexp = 0.0;

        std::string variableb = "b";
        std::string variablec = "c";

        // Setup the string vector balancEquations, to handle b and c numerically
        auto balanceEquations = balanceEquationsHandler(reactantsCompounds, reactantsCoeff, productsCompounds, productsCoeff, selectedKpExp, midx);

        // Check which balance equation contains b and which c, then calculate the respective variable
        // eq example: "4.00 = 3.00*2 + b*3"
        for (auto& eq : balanceEquations) {
            size_t pos_b = eq.find("b");
            if (pos_b != std::string::npos) {
                // Calculate b
                b = solve_linear_equation(evaluate_numeric_expressions(eq), variableb);
            }
            size_t pos_c = eq.find("c");
            if (pos_c != std::string::npos) {
                // Calculate c
                c = solve_linear_equation(evaluate_numeric_expressions(eq), variablec);
            }
        }

        // Calculate total a+b+c
        double totalVariables = a + b + c;

        //System::Windows::Forms::MessageBox::Show("a: " + a.ToString() + "\n" + "b: " + b.ToString() + "\n" + "c: " + c.ToString());

        // If any of these is 0, experimental kp will be NaN, so ignore this iteration
        if (b == 0 && c == 0 || totalVariables == 0) { continue; }

        // Setup the string vector to evaluate the right enthalpy
        std::vector<std::string> symbolicProductsCoeffs = symbolicProductsCoeffHandler(productsCompounds, productsCoeff, selectedKpExp);

        // Setup valued coefficients for right enthalpy
        std::vector<double> evalProductsCoeffs = simpleEvalHandler(symbolicProductsCoeffs, a, b, c);

        // Calculate right enthalpy of formation
        double rightEnth = 0.0;
        for (int p = 0; p < productsCompounds.size(); ++p) {
            rightEnth += evalProductsCoeffs[p] * enthalpies[productsCompounds[p]];
        }

        // Target enthalpy of formation
        double targetEnth = leftEnth - rightEnth;

        // If c AND b exist, calculate extended experimental kp
        if (b != 0 && c != 0) {
            // Normally b is the first balance equation, but if not, reverse the recombination expression exponents
            if (balanceEquations[0].find("b") != std::string::npos) {
                kpexp = ((a / totalVariables) / ((pow(b / totalVariables, abs(exponents[1]))) * (pow(c / totalVariables, abs(exponents[2]))))) * pow(pressure, deltn);
                //System::Windows::Forms::MessageBox::Show("kpexp 1: " + kpexp.ToString());
            }
            else {
                kpexp = ((a / totalVariables) / ((pow(b / totalVariables, abs(exponents[2]))) * (pow(c / totalVariables, abs(exponents[1]))))) * pow(pressure, deltn);
            }

        } // Otherwise, only a and b
        else if (b != 0) {
            kpexp = ((a / totalVariables) / (pow(b / totalVariables, abs(exponents[1])))) * pow(pressure, deltn);
            //System::Windows::Forms::MessageBox::Show("kpexp 2: " + kpexp.ToString());
        }
        else { // otherwise, must be a and c (should not be possible, but just in case)
            kpexp = ((a / totalVariables) / (pow(c / totalVariables, abs(exponents[1])))) * pow(pressure, deltn);
            //System::Windows::Forms::MessageBox::Show("kpexp 3: " + kpexp.ToString());
        }

        //System::Windows::Forms::MessageBox::Show("kpexp: " + kpexp.ToString());

        // At this point, check if experimental kp is not NaN to continue, otherwise go to the next step in the loop
        if (isnan(kpexp)) { continue; };

        // Calculate the kp error
        double kperror = kpexp - kptheor;

        //System::Windows::Forms::MessageBox::Show("A: " + a.ToString() + "\n" + "B: " + b.ToString() + "\n" + "C: " + c.ToString() + "\n" + "Left Enthalpy : " + leftEnth.ToString() + "\n" + "Right Enthalpy : " + rightEnth.ToString() + "\n"
        //+ "Target Enthalpy: " + targetEnth.ToString() + "\n" + "\n" + "Theoretical Kp: " + kptheor.ToString() + "\n" 
        //+ "Experimental Kp: " + kpexp.ToString() + "\n" + "Kp Error: " + kperror.ToString() + "\n" + "Kp Tolerance: " + kpTolerance.ToString());


        // Track best x solution
        if (abs(kperror) < bestXError) {
            bestXError = abs(kperror);
            bestX = midx;
        }

        if (abs(kperror) <= kpTolerance) {
            //System::Windows::Forms::MessageBox::Show("Correct Kp fraction: " + a.ToString());
            return { {1},{targetEnth},{evalProductsCoeffs},{a},{b},{c} };
        }

        // Update x search bounds
        if (kperror > 0) {
            highx = midx; // Too high, search lower half
        }
        else {
            lowx = midx; // Too low, search upper half
        }

        // Early exit if the range is too small
        if ((highx - lowx) < 0.000000000000000000000000000001) { //1E-30 kp precision
            //System::Windows::Forms::MessageBox::Show("X ran out of precision");
            return { {0},{0},{0,0},{0},{0},{0} };
        }

        //System::Windows::Forms::MessageBox::Show("Kp fraction: " + a.ToString());

    }


    //return { {0},{0},{0,0} };

}
*/

//
// EXTENDED INCOMPLETE COMBUSTION SECTION ------------------------------------------------------------------------------------------
//


//
// MAIN BEHAVIOR SECTION --------------------------------------------------------------------------------------------------
//

namespace NativeWinGUIC {
    System::Void MainForm::btnRun_Click(System::Object^ sender, System::EventArgs^ e) {

        // Extract from the reaction textboxes
        String^ Reactantsinput = tbReactants->Text;
        std::string convReactantsinput = msclr::interop::marshal_as<std::string>(Reactantsinput);
        String^ Productsinput = tbProducts->Text;
        std::string convProductsinput = msclr::interop::marshal_as<std::string>(Productsinput);

        // Extract from the pressure textbox
        String^ pressureInput = tbPressure->Text;
        double PressureNum = 0.0;
        if (!String::IsNullOrEmpty(pressureInput)) {
            if (rdbPressureATM->Checked) {
                PressureNum = stod(msclr::interop::marshal_as<std::string>(pressureInput));
            }
            if (rdbPressureKPA->Checked) {
                PressureNum = 0.0098692327 * stod(msclr::interop::marshal_as<std::string>(pressureInput));
            }
            if (rdbPressurePSI->Checked) {
                PressureNum = 0.0680459639 * stod(msclr::interop::marshal_as<std::string>(pressureInput));
            }
        }

        // Extract selected item in recombination textbox
        std::vector<std::string> recombSelectedStrings;
        // Loop through all selected items, and if valid, add them
        for each (Object ^ item in lstbRecombOptions->SelectedItems) {
            String^ text = lstbRecombOptions->GetItemText(item);
            if (!String::IsNullOrEmpty(text)) {
                recombSelectedStrings.push_back(msclr::interop::marshal_as<std::string>(text));
            }
        }

        // Verify valid reaction input
        if (!String::IsNullOrEmpty(Reactantsinput) && !String::IsNullOrEmpty(Productsinput) && !tbReactants->Text->Contains("e.g. N2H4 3N2 H2") && !tbProducts->Text->Contains("e.g. 2NH3 N2 H2")) {
            if (ckbRecombination->Checked && PressureNum) {
                String^ recombPrint = "";
                for each (Object ^ item in lstbRecombOptions->SelectedItems) {
                    String^ text = lstbRecombOptions->GetItemText(item);
                    if (!String::IsNullOrEmpty(text)) {
                        recombPrint += text + "\n";
                    }
                }

                MessageBox::Show("Reaction to process: " + Reactantsinput + " -> " + Productsinput + "\n" + "Reaction Pressure: " + PressureNum + " atm" + "\n" + "The following recombination effects will be considered: " + "\n" + recombPrint);
            }
            if (!ckbRecombination->Checked) {
                MessageBox::Show("Reaction to process: " + Reactantsinput + " -> " + Productsinput);
            }

        }
        else { MessageBox::Show("Incomplete reaction input"); }

        // Initialize Adiabatic flame temperature variable "aft"
        double aft = 0.0;
        std::vector<double> solutionsVector;

        // Determine type of calculation from checkbox
        if (!ckbRecombination->Checked) {
            aft = completeCombustion(convReactantsinput, convProductsinput);
        }
        else {
            auto incompVec = incompleteCombustion(convReactantsinput, convProductsinput, 0.00001, recombSelectedStrings, PressureNum);
            aft = std::get<0>(incompVec);
            solutionsVector = std::get<1>(incompVec);
        }

        System::String^ solutionsPrintAppendix = "Error in solutions printing";
        if (!solutionsVector.empty()) {
            solutionsPrintAppendix = "";
            for (size_t u = 0; u < solutionsVector.size(); ++u) {
                char var = 'a' + u;
                solutionsPrintAppendix += var + ": " + (solutionsVector[u]).ToString() + "\n";
            }
        }

        //Final Temperature Output
        System::String^ msg = "Enter valid input and options";
        if (rdbLogSIMPLE->Checked) {
            if (rdbOutK->Checked) {
                msg = "Adiabatic Flame Temperature: " + (aft).ToString() + " K";
            }
            if (rdbOutF->Checked) {
                msg = "Adiabatic Flame Temperature: " + ((aft - 273.15) * (9.0 / 5.0) + 32.0).ToString() + " °F";
            }
            if (rdbOutC->Checked) {
                msg = "Adiabatic Flame Temperature: " + (aft - 273.15).ToString() + " °C";
            }
        }
        if (rdbLogFULL->Checked && ckbRecombination->Checked) {
            if (rdbOutK->Checked) {
                msg = "Adiabatic Flame Temperature: " + (aft).ToString() + " K" + "\n" + solutionsPrintAppendix;
            }
            if (rdbOutF->Checked) {
                msg = "Adiabatic Flame Temperature: " + ((aft - 273.15) * (9.0 / 5.0) + 32.0).ToString() + " °F" + "\n" + solutionsPrintAppendix;
            }
            if (rdbOutC->Checked) {
                msg = "Adiabatic Flame Temperature: " + (aft - 273.15).ToString() + " °C" + "\n" + solutionsPrintAppendix;
            }
        }
        if (rdbLogFULL->Checked && !ckbRecombination->Checked) {
            MessageBox::Show("Only simple output for non-recombining reactions!");
        }
        if (rdbLogDEBUG->Checked) {
            MessageBox::Show("Dev feature, work in progress");
        }

        MessageBox::Show(msg);
    }

    System::Void MainForm::btnHelp_Click(System::Object^ sender, System::EventArgs^ e) {
        Form^ hF = gcnew HelpForm;
        hF->Show();
    }

}



[STAThread]
int main(cli::array<System::String^>^ args)
{
	System::Windows::Forms::Application::EnableVisualStyles();
	System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);
	NativeWinGUIC::MainForm form;
    NativeWinGUIC::HelpForm form2;
	System::Windows::Forms::Application::Run(%form);
	return 0;


}