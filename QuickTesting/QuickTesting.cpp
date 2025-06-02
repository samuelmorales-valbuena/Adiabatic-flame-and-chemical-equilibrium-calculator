//Samuel Morales Valbuena - 202179820//
//780039 - Propulsion Systems//

#define _CRT_SECURE_NO_WARNINGS
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
#include <exprtk.hpp>

// This is to make writing less tedious
using namespace std;

// Map of compounds to their atom count
static map<string, map<string, int>> atom_counts = {
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
static map<string, int> enthalpies = {
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
static map<string, vector<pair<pair<double, double>, vector<double>>>> compoundVectors = {
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
static map<vector<string>, tuple<vector<tuple<double, double, vector<double>>>, vector<double>>> kpVectors = {
    // kp1 data
    {{"O","O2"},{{
        {298,1500, {-5.25e-11, 2.30e-07, -3.78e-04, 2.89e-01, -9.84e+01}},
        {1500,5000,{0.00e+00, 1.86e-10, -2.35e-06, 1.05e-02, -1.64e+01}}
        }, {1, -1.0 / 2}
    }},
    // kp2 data
    {{"H","H2"},{{
        {298,1500,{-4.63e-11,2.20e-07,-3.33e-04,2.55e-01,-8.68e+01}},
        {1500,5000,{0.00e+00,1.65e-10,-2.08e-06,9.40e-03,1.46e+01}}
        }, {1, -1.0 / 2}

    }},
    // kp3 data
    {{"OH","O2","H2"},{{
        {298,1500,{-8.97e-12,3.93e-08,-6.46e-05,4.93e-02,-1.65e+01}},
        {1500,5000,{0.00e+00,3.04e-11,-3.81e-07,1.70e-03,-2.44e+00}}
        }, {1, -1.0 / 2, -1.0 / 2}

    }},
    // kp4 data
    {{"H2O","H2","O2"},{{
        {298,1500,{5.12e-11,-2.24e-07,3.69e-04,-2.82e-01,9.68e+01}},
        {1500,5000,{0.00e+00,-1.86e-10,2.34e-06,-1.05e-02,1.67e+01}}
        }, {1, -1.0, -1.0 / 2}

    }},
    // kp5 data
    {{"N","N2"},{{
        {298,1500,{-7.61e-11,3.33e-07,-5.47e-04,4.18e-01,-1.44e+02}},
        {1500,5000,{0.00e+00,2.68e-10,-3.38e-06,1.52e-02,-2.51e+01}}
        }, {1, -1.0 / 2}

    }},
    // kp6 data
    {{"NO","N2","O2"},{{
        {298,1500,{-1.92e-11,8.41e-08,-1.38e-04,1.06e-01,-3.64e+01}},
        {1500,5000,{0.00e+00,6.69e-11,-8.44e-07,3.80e-03,6.45e+00}}
        }, {1, -1.0, -1.0 / 2}

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
        }, {1, -1.0, -1.0 / 2}

    }},
    // kp10 data
    {{"CO2","C","O2"},{{
        {298,1500,{8.38e-11,-3.66e-07,6.02e-04,-4.60e-01,1.61e+02}},
        {1500,4000,{0.00e+00,-4.90e-10,5.27e-06,-2.06e-02,3.44e+01}}
        }, {1, -1.0, -1.0}

    }},
    // kp11 data
    {{"CH4","C","H2"},{{
        {298,1500,{1.51e-11,-6.63e-08,1.10e-04,-8.64e-02,2.65e+01}}
        }, {1, -1.0, -2.0}

    }},
    // kp12 data
    {{"C2H2","C","H2"},{{
        {298,1500,{-4.84e-11,2.12e-07,-3.48e-04,2.65e-01,-8.99e+01}}
        }, {1, -2.0, -1.0}

    }},
    // kp13 data
    {{"Cl","Cl2"},{{
        {298,1500,{-2.57e-11,1.12e-07,-1.85e-04,1.42e-01,-4.70e+01}}
        }, {1, -1.0 / 2}

    }},
    // kp14 data
    {{"HCl","H2","Cl2"},{{
        {298,1500,{1.96e-11,-8.56e-08,1.41e-04,-1.08e-01,3.83e+01}}
        }, {1, -1.0 / 2, -1.0 / 2}

    }},
    // kp15 data
    {{"NH","N2","H2"},{{
        {600,2000,{-8.73e-12,5.58e-08,-1.37e-04,1.62e-01,-9.04e+01}},
        {2000,4000,{0.00e+00,2.80e-10,-3.33e-06,1.46e-02,-2.69e+01}}
        }, {1, -1.0 / 2, -1.0 / 2}

    }},
    // kp16 data
    {{"NH3","N2","H2"},{{
        {600,2000,{1.08e-12,-7.02e-09,1.76e-05,-2.14e-02,6.48e+00}},
        {2000,4000,{0.00e+00,-4.46e-11,5.26e-07,-2.20e-03,-1.95e+00}}
        }, {1, -1.0 / 2, -3.0 / 2}

    }},
    // kp17 data
    {{"CH2","C","H2"},{{
        {600,2000,{-8.97e-12,5.73e-08,-1.41e-04,1.66e-01,-9.07e+01}},
        {2000,4000,{0.00e+00,2.83e-10,-3.37e-06,1.47e-02,-2.56e+01}}
        }, {1, -1.0, -1.0}

    }},
    // kp18 data
    {{"NO2","NO","O2"},{{
        {300,1600,{-9.84e-12,4.53e-08,-7.82e-05,6.24e-02,-1.92e+01}},
        {1600,3000,{0.00e+00,1.80e-10,-1.48e-06,4.50e-03,-2.45e+00}}
        }, {1, -1.0, -1.0 / 2}

    }},
    // kp19 data
    {{"NO","N2","O2"},{{
        {300,1800,{-1.03e-11,5.27e-08,-9.98e-05,8.66e-02,-3.32e+01}},
        {1800,5000,{0.00e+00,5.23e-11,-6.88e-07,3.30e-03,-5.87e+00}}
        }, {1, -1.0 / 2, -1.0 / 2}

    }}

};



// Function to get the appropriate coefficient vector for a compound at a given temperature
vector<double> getCompoundVector(const string& compound, double temperature) {

    // Check if the compound exists in map
    if (compoundVectors.find(compound) == compoundVectors.end()) {
        throw runtime_error("Compound " + compound + " not found in database");
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

    throw runtime_error("Temperature " + to_string(temperature) + " out of range for compound " + compound);
}

// Function for the integrated expressions
double intCp(const vector<double>& coef, double rt) {
    return coef[0] * rt +
        coef[1] * pow(rt, 2) / 2 +
        coef[2] * pow(rt, 3) / 3 +
        coef[3] * pow(rt, 4) / 4 -
        coef[4] / rt;
}

// Helper function to split a string by spaces
vector<string> splitString(const string& input) {
    vector<string> result;
    istringstream iss(input);
    string compound;

    while (iss >> compound) {
        result.push_back(compound);
    }

    return result;
}

// Function to find the overlapping temperature range for a list of compounds
pair<double, double> findOverlappingTemperatureRange(const vector<string>& compounds) {
    if (compounds.empty()) {
        throw runtime_error("No compounds provided");
    }

    double minTemp = -INFINITY;
    double maxTemp = INFINITY;

    // For each compound
    for (const auto& compound : compounds) {
        // Check if compound exists in database
        if (compoundVectors.find(compound) == compoundVectors.end()) {
            throw runtime_error("Compound " + compound + " not found in database");
        }

        // Find the min and max temperature across all ranges for this compound
        double compoundMinTemp = INFINITY;
        double compoundMaxTemp = -INFINITY;

        for (const auto& range : compoundVectors[compound]) {
            double rangeMinTemp = range.first.first;
            double rangeMaxTemp = range.first.second;

            compoundMinTemp = min(compoundMinTemp, rangeMinTemp);
            compoundMaxTemp = max(compoundMaxTemp, rangeMaxTemp);
        }

        // Update the overall min and max
        minTemp = max(minTemp, compoundMinTemp);
        maxTemp = min(maxTemp, compoundMaxTemp);
    }

    // Check if we have a valid overlapping range
    if (minTemp > maxTemp) {
        throw runtime_error("No overlapping temperature range exists for the specified compounds");
    }

    return { minTemp, maxTemp };
}

// Function to check if kp is needed
optional<vector<string>> checkifKpIsNeeded(const vector<string>& potentials) {
    if (potentials.empty()) {
        throw runtime_error("No products provided");
    }

    // For the products
    for (const auto& [kpCompounds, kpData] : kpVectors) {
        bool allFound = all_of(
            kpCompounds.begin(),
            kpCompounds.end(),
            [&potentials](const string& compound) {
                return find(potentials.begin(), potentials.end(), compound) != potentials.end();
            }
        );

        if (allFound) {
            // At least one Kp entry matches all required compounds, write it (not done yet)
            return kpCompounds;
        }
    }

    // If it got to here, no Kp vector fully matched
    return nullopt;
}




int main() {

    // Enthalpy of formation (J/mol) from NIST and Wiki
    int dfH_O = 249180;
    int dfH_O2 = 0;
    int dfH_H = 218000;
    int dfH_H2 = 0;
    int dfH_OH = 38990;
    int dfH_H2O = -241818;
    int dfH_N = 472680;
    int dfH_N2 = 0;
    int dfH_NO = 90290;
    int dfH_CO = -110530;
    int dfH_CO2 = -393520;
    int dfH_CH4 = -74850;
    int dfH_C2H2 = 226700;
    int dfH_Cl = 121300;
    int dfH_Cl2 = 0;
    int dfH_HCl = -92310;
    int dfH_NH = 376560;
    int dfH_NH3 = -45940;
    int dfH_CH2 = 386390;
    int dfH_NO2 = 33100;
    int dfH_N2H4 = 95400;

    // Reference temp in K, only changes when the enthalpies of formation change anyways
    double t0 = 298;


    try {

        // Provide the list of compounds
        cout << "Available compounds: O2 H H2 OH H2O N N2 NO CO CO2 CH4 C2H2 Cl Cl2 HCl NH NH3 CH2 NO2" << endl;

        // Ask user for reactants
        string reactantsInput;
        cout << "Enter reactants separated by spaces: ";
        getline(cin, reactantsInput);
        vector<string> reactants = splitString(reactantsInput);

        // Ask user for products
        string productsInput;
        cout << "Enter products separated by spaces: ";
        getline(cin, productsInput);
        vector<string> products = splitString(productsInput);

        // Ask user for balance coefficients
        string balanceInput;
        vector<double> balance;
        cout << "Enter balance coefficients separated by spaces: ";
        getline(cin, balanceInput);
        istringstream iss(balanceInput);
        double numforcomp;
        while (iss >> numforcomp) {
            balance.push_back(numforcomp);
        }

        // Display the reaction
        cout << "\nProcessing reaction: ";
        for (size_t i = 0; i < reactants.size(); ++i) {
            cout << reactants[i];
            if (i < reactants.size() - 1) cout << " + ";
        }
        cout << " <-> ";
        for (size_t i = 0; i < products.size(); ++i) {
            cout << products[i];
            if (i < products.size() - 1) cout << " + ";
        }
        cout << endl << endl;

        // Combine all compounds for range determination
        vector<string> allCompounds;
        allCompounds.insert(allCompounds.end(), reactants.begin(), reactants.end());
        allCompounds.insert(allCompounds.end(), products.begin(), products.end());

        // Find the overlapping temperature range
        pair<double, double> tempRange = findOverlappingTemperatureRange(allCompounds);
        cout << "Valid temperature range for all compounds: " << tempRange.first << " K to " << tempRange.second << " K" << endl << endl;

        // x ranges from mathematica plots
        vector<long double> xfiltered;
        for (int i = 0; i < 10000; ++i) {
            long double x1 = 0.00034 + i * (1.5 - 0.00034) / 9999.0;
            xfiltered.push_back(x1);
        }

        // Print full numbers later
        int precision = numeric_limits<long double>::max_digits10;

        // Adiabatic range
        int nTempSteps = 20000;
        double t_min = tempRange.first, t_max = tempRange.second;
        double t_step = (t_max - t_min) / (nTempSteps - 1);

        // Left enthalpy
        double leftenth = 0.0;
        for (int i = 0; i < reactants.size(); ++i) {
            leftenth += balance[i] * enthalpies[reactants[i]];
        }
        //cout << leftenth << endl;

        // Right enthalpy
        double rightenth = 0.0;
        for (int i = 0; i < products.size(); ++i) {
            rightenth += balance[i] * enthalpies[products[i]];
        }
        //cout << rightenth << endl;

        // Target enthalpy
        double targetenth = leftenth - rightenth;
        //cout << targetenth << endl;

        // Utility vectors for printing
        vector<pair<double, double>> t_plus_entherrorvec;
        vector<pair<double, double>> t_plus_xperrorvec;
        double x = 0.0;



        if (checkifKpIsNeeded(products)) {





            cout << "Recombination effects will be considered" << endl;

            string pstring;
            cout << "Enter chamber pressure in atm:" << endl;
            getline(cin, pstring);
            double pressure = stod(pstring);

            string xmolarstring, ymolarstring, zmolarstring;
            cout << "Enter independent molar fraction (e.g. x/(3-x)):" << endl;
            getline(cin, xmolarstring);
            cout << "Enter first dependent molar fraction (e.g. (2-x)/(2*(3-x))):" << endl;
            getline(cin, ymolarstring);
            cout << "Enter second dependent molar fraction (e.g. (4-3*x)/(2*(3-x))):" << endl;
            getline(cin, zmolarstring);



            exprtk::symbol_table<double> symtab;
            symtab.add_variable("x", x);
            symtab.add_constants();

            exprtk::expression<double> xmolar_expr, ymolar_expr, zmolar_expr;
            xmolar_expr.register_symbol_table(symtab);
            ymolar_expr.register_symbol_table(symtab);
            zmolar_expr.register_symbol_table(symtab);

            exprtk::parser<double> parser;
            if (!parser.compile(xmolarstring, xmolar_expr) ||
                !parser.compile(ymolarstring, ymolar_expr) ||
                !parser.compile(zmolarstring, zmolar_expr)) {
                cerr << "Error compiling one of the expressions." << endl;
                return 1;
            }



            // Main loop, temps
            for (int i = 0; i < nTempSteps; ++i) {
                double t = t_min + i * t_step;
                double T = t / 1000.0;
                double T0 = t0 / 1000.0;
                double computedenth = 0.0;

                optional<vector<string>> matchingkey = checkifKpIsNeeded(products);

                // Unpack the tuple from the map
                const auto& [kpTuples, exponents] = kpVectors.at(*matchingkey);

                // Find the matching coefficient set for the current temperature
                auto it = find_if(kpTuples.begin(), kpTuples.end(), [t](const auto& entry) {
                    double Tmin = get<0>(entry);
                    double Tmax = get<1>(entry);
                    return t >= Tmin && t <= Tmax;
                    });

                if (it == kpTuples.end()) {
                    continue;
                }

                //Delta-n
                double deltn = accumulate(exponents.begin(), exponents.end(), 0.0);

                // A-E
                const std::vector<double>& coeffs = std::get<2>(*it);

                // Unpack coefficients for clarity
                double A = coeffs[0];
                double B = coeffs[1];
                double C = coeffs[2];
                double D = coeffs[3];
                double E = coeffs[4];

                double kptheor = pow(10, A * pow(t, 4) + B * pow(t, 3) + C * pow(t, 2) + D * t + E);


                for (double xval : xfiltered) {

                    x = xval;

                    double xmolar = xmolar_expr.value();
                    double ymolar = ymolar_expr.value();
                    double zmolar = zmolar_expr.value();

                    // Vector of symbolic coefficients
                    vector<double> symbmolarvec = { xmolar, ymolar, zmolar };

                    // Left enthalpy
                    leftenth = 0.0;
                    for (int i = 0; i < reactants.size(); ++i) {
                        leftenth += balance[i] * enthalpies[reactants[i]];
                    }
                    //cout << leftenth << endl;

                    // Right enthalpy
                    rightenth = x * enthalpies[products[0]];
                    for (int i = 1; i < products.size(); ++i) {
                        rightenth += symbmolarvec[i] * enthalpies[products[i]];
                    }
                    //cout << rightenth << endl;

                    // Target enthalpy
                    double targetenth = leftenth - rightenth;
                    //cout << targetenth << endl;


                    double kpexp;
                    if (zmolar) {
                        kpexp = (xmolar / ((pow(ymolar, abs(exponents[1]))) * (pow(zmolar, abs(exponents[2]))))) * pow(pressure, deltn);
                    }
                    else {
                        kpexp = (xmolar / (pow(ymolar, abs(exponents[1])))) * (pow(pressure, deltn));
                    }


                    //double kpexpgood = (4 * x * (3 - x)) / (pow(2 - x, 0.5) * pow(4 - 3 * x, 1.5));
                    double kperror = abs(1 - (kpexp / kptheor)) * 100;

                    //cout << "kpbad: " << kpexp << " kpgood: " << kpexpgood << endl;
                    //cout << " temp: " << t << " x: " << x << " theoretic kp: " << kptheor << " exp kp: " << kpexp << " kp error: " << kperror << endl;

                    if (kperror < 4) {


                        for (int i = 0; i < products.size(); ++i) {
                            const auto& names = products[i];
                            const auto& cpdata = compoundVectors[names];

                            // Find the Cp coefficients valid for temperature T
                            auto it = find_if(cpdata.begin(), cpdata.end(), [t](const auto& entry) {
                                double tmin = entry.first.first;
                                double tmax = entry.first.second;
                                return t >= tmin && t <= tmax;
                                });


                            const vector<double>& coeffscp = it->second;

                            if (i == 0) {
                                computedenth = (x * (intCp(coeffscp, T) - intCp(coeffscp, T0))) * 1000;
                            }
                            else {
                                computedenth += (symbmolarvec[i] * (intCp(coeffscp, T) - intCp(coeffscp, T0))) * 1000;
                            }

                        }


                        double entherror = abs(1 - (computedenth / targetenth)) * 100;

                        //cout << "Temperature: " << t << endl;
                        //cout << "Target enth: " << targetenth << endl;
                        //cout << "Computed enth: " << computedenth << endl;
                        //cout << "Enth error: " << entherror << "%" << endl;

                        if (entherror < 5) {
                            t_plus_entherrorvec.push_back(make_pair(t, entherror));
                            t_plus_xperrorvec.push_back(make_pair(t, kperror));
                        }

                    }

                }
            }





        }

        else {

            // Main loop, temps
            for (int i = 0; i < nTempSteps; ++i) {
                double t = t_min + i * t_step;
                double T = t / 1000.0;
                double T0 = t0 / 1000.0;
                double computedenth = 0.0;

                for (int i = 0; i < products.size(); ++i) {
                    const auto& names = products[i];
                    const auto& cpdata = compoundVectors[names];

                    // Find the Cp coefficients valid for temperature T
                    auto it = find_if(cpdata.begin(), cpdata.end(), [t](const auto& entry) {
                        double tmin = entry.first.first;
                        double tmax = entry.first.second;
                        return t >= tmin && t <= tmax;
                        });

                    if (it == cpdata.end()) {
                        throw runtime_error("No Cp coefficients found for " + names + " at T = " + to_string(t));
                    }

                    const vector<double>& coeffs = it->second;

                    computedenth += (balance[i] * (intCp(coeffs, T) - intCp(coeffs, T0))) * 1000;
                    //cout << t << " means " << computedenth << endl;
                }


                double entherror = abs((computedenth - targetenth) / targetenth) * 100;

                t_plus_entherrorvec.push_back(make_pair(t, entherror));

            }

        }


        /*//Display t and associated enthalpy error for debugging
        for (auto& x : t_plus_entherrorvec) {
            cout << x.first << ":" << x.second << endl;
        }*/


        // Display the min errors
        if (!t_plus_entherrorvec.empty()) {
            auto min_pair = *min_element(
                t_plus_entherrorvec.begin(),
                t_plus_entherrorvec.end(),
                [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; }
            );
            cout << "Minimum h error % at T = " << min_pair.first << " K: " << min_pair.second << " %" << " with a fraction x of: " << x << endl;
        }
        // Display the min errors
        if (!t_plus_xperrorvec.empty()) {
            auto min_pair = *min_element(
                t_plus_xperrorvec.begin(),
                t_plus_xperrorvec.end(),
                [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; }
            );
            cout << "Minimum kp error % at T = " << min_pair.first << " K: " << min_pair.second << " %" << " with a fraction x of: " << x << endl;
        }

    }
    catch (const exception& e) {
        cerr << "General error: " << e.what() << endl;
    }

    //// Append to csv
    //ofstream file("output.csv", ios::app);

    //

    //if (file.is_open()) {
    //    size_t n = t_plus_entherrorvec.size();

    //    // Get current time
    //    auto now = chrono::system_clock::now();
    //    time_t now_time = chrono::system_clock::to_time_t(now);

    //    // Write timestamp
    //    file << "\n--- " << ctime(&now_time) << "---\n";

    //    for (size_t i = 0; i < n; ++i) {
    //        file << t_v[i] << "," << x_v[i] << "," << y_v[i] << "," << z_v[i] << "," << h_error[i] << "," << x_kp_error[i] << "\n";
    //    }

    //    file.close();
    //    cout << "Data appended" << endl;
    //}

    cout << "Press enter to end" << endl;
    cin.get();
    return 0;
}