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
    int NhipTim;
    int diagnosis; // 0: không mắc bệnh, 1: mắc bệnh tim
};

double KhoangCachEuclidean(const Patient& p1, const Patient& p2) {
    double d_age = p1.age - p2.age;
    double d_cholesterol = p1.cholesterol - p2.cholesterol;
    double d_NhipTim = p1.NhipTim - p2.NhipTim;
    return sqrt(d_age * d_age + d_cholesterol * d_cholesterol + d_NhipTim * d_NhipTim);
}

int DuDoanKNN(const std::vector<Patient>& patients, const Patient& newPatient, int k) {
    std::vector<std::pair<double, int> > distancesAndDiagnosis;

    for (std::vector<Patient>::const_iterator it = patients.begin(); it != patients.end(); ++it) {
    	const Patient& patient = *it;
        double distance = KhoangCachEuclidean(newPatient, patient);
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
    std::ifstream dataFile("heart_disease_data.txt");

    if (dataFile.is_open()) {
        std::string line;
        while (std::getline(dataFile, line)) {
            std::istringstream ss(line);
            Patient patient;
            ss >> patient.age >> patient.cholesterol >> patient.NhipTim >> patient.diagnosis;
            patients.push_back(patient);
        }
        dataFile.close();
    } else {
        std::cerr << "Failed to open data file." << std::endl;
        return 1;
    }

    Patient newPatient = {45, 210, 150, 0}; // chèn các giá trị của bệnh nhân mới cần chẩn đoán

    int k = 3;
    int predictedDiagnosis = DuDoanKNN(patients, newPatient, k);

    if (predictedDiagnosis == 0) {
        std::cout << "Benh nhan khong mac banh tim." << std::endl;
    } else {
        std::cout << "Benh nhan mac benh tim." << std::endl;
    }

    return 0;
}
