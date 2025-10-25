#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

double parseNumber(const char* str) {
    double result = 0.0;
    double fraction = 0.0;
    double divisor = 1.0;
    bool negative = false;
    bool afterDot = false;
    
    while (*str == ' ') str++;
    
    if (*str == '-') {
        negative = true;
        str++;
    } else if (*str == '+') {
        str++;
    }
    
    while (*str != '\0' && *str != ';' && *str != '\n') {
        if (*str == '.') {
            afterDot = true;
        } else if (*str >= '0' && *str <= '9') {
            int digit = *str - '0';
            if (!afterDot) {
                result = result * 10 + digit;
            } else {
                divisor *= 10.0;
                fraction += digit / divisor;
            }
        } else {
            break;
        }
        str++;
    }

    result += fraction;
    if (negative) result = -result;
    return result;
}

double extractValue(const string& line, const char* label) {
    const char* p = line.c_str();
    const char* found = nullptr;

    while (*p != '\0') {
        const char* start = p;
        const char* lab = label;
        while (*start && *lab && *start == *lab) {
            start++;
            lab++;
        }
        if (*lab == '\0') { 
            found = start;
            break;
        }
        p++;
    }

    if (found) {
        return parseNumber(found);
    } else {
        return NAN;
    }
}

int main() {
    vector<string> data = {
        "ALT:1230;VEL:245;TEMP:-5.4;PRES:101.8",
        "ALT:1265;VEL:248;TEMP:-5.2;PRES:101.7",
        "ALT:1250;VEL:242;TEMP:-5.8;PRES:101.9",
        "ALT:1242;VEL:241;TEMP:-5.1;PRES:101.1",
        "ALT:1228;VEL:238;TEMP:-5.3;PRES:101.6"
    };
    vector<double> alt, vel, temp, press;
    
    for (const auto& line : data) {
        double a = extractValue(line, "ALT:");
        double v = extractValue(line, "VEL:");
        double t = extractValue(line, "TEMP:");
        double p = extractValue(line, "PRESS:");
        alt.push_back(a);
        vel.push_back(v);
        temp.push_back(t);
        press.push_back(p);
    }
    
    double maxAlt = alt[0], avgVel = 0, minTemp = temp[0];
    for (size_t i = 0; i < temp.size(); ++i) {
        avgVel += vel[i];
        if (temp[i] < minTemp) minTemp = temp[i];
        if (alt[i] > maxAlt) maxAlt = alt[i];
    }
    avgVel /= vel.size();

    cout << "Max altitude: " << maxAlt << " m\n";
    cout << "Average velocity: " << avgVel << " m/s\n";
    cout << "Min temperature: " << minTemp << " °C\n";
    return 0;
}
