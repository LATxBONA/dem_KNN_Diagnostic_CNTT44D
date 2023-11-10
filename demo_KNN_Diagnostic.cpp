#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

struct Patient {
    int age;
    int cholesterol;
    int max_heart_rate;
    int diagnosis; // 0: không mắc bệnh, 1: mắc bệnh tim
};

double euclideanDistance(const Patient& p1, const Patient& p2) {
    double d_age = p1.age - p2.age;
    double d_cholesterol = p1.cholesterol - p2.cholesterol;
    double d_max_heart_rate = p1.max_heart_rate - p2.max_heart_rate;
    return sqrt(d_age * d_age + d_cholesterol * d_cholesterol + d_max_heart_rate * d_max_heart_rate);
}

int predictKNN(const std::vector<Patient>& patients, const Patient& newPatient, int k) {
    std::vector<std::pair<double, int>> distancesAndDiagnosis;

    for (const Patient& patient : patients) {
        double distance = euclideanDistance(newPatient, patient);
        distancesAndDiagnosis.push_back({distance, patient.diagnosis});
    }

    std::sort(distancesAndDiagnosis.begin(), distancesAndDiagnosis.end());

    int diagnosisCount[2] = {0, 0}; // 0: không mắc bệnh, 1: mắc bệnh tim

    for (int i = 0; i < k; ++i) {
        diagnosisCount[distancesAndDiagnosis[i].second]++;
    }

    return (diagnosisCount[0] > diagnosisCount[1]) ? 0 : 1;
}

int main() {
    std::vector<Patient> patients;
    std::ifstream dataFile("heart_disease_data.csv");

    if (dataFile.is_open()) {
        std::string line;
        while (std::getline(dataFile, line)) {
            std::istringstream ss(line);
            Patient patient;
            ss >> patient.age >> patient.cholesterol >> patient.max_heart_rate >> patient.diagnosis;
            patients.push_back(patient);
        }
        dataFile.close();
    } else {
        std::cerr << "Failed to open data file." << std::endl;
        return 1;
    }

    Patient newPatient = {45, 210, 150, 0}; // Chèn các giá trị của bệnh nhân mới cần chẩn đoán

    int k = 3;
    int predictedDiagnosis = predictKNN(patients, newPatient, k);

    if (predictedDiagnosis == 0) {
        std::cout << "Bệnh nhân không mắc bệnh tim." << std::endl;
    } else {
        std::cout << "Bệnh nhân mắc bệnh tim." << std::endl;
    }

    return 0;
}
