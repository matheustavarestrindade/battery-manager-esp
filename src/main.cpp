#include <Arduino.h>

#include "HomeAutomation.h"

#define ANALOG_BATTERY_1_PIN 39  //
#define ANALOG_BATTERY_2_PIN 35  // D35 //USE FROM 32 TO 39 AS OTHERS ARE FOR WIFI

char* device_name = "Battery Monitor";
char* device_type = "battery_monitor_v1";

void loadVoltages();
double calculate_adc_voltage(int adcValue);
double calculate_baterry_soc(double baterry_voltage);
HomeAutomation automation(device_name, device_type);

double BATTERY_1_VOLTAGE = 0.0;
double BATTERY_1_SOC = 0.0;
double BATTERY_2_VOLTAGE = 0.0;
double BATTERY_2_SOC = 0.0;

void handleRequest() {
    // Switch relay on for 2 sec
    String data = "{";
    data += "\"batteries\": [";
    data += "{";
    data += "\"voltage\": ";
    data += String(BATTERY_1_VOLTAGE);
    data += ",";
    data += "\"SOC\": ";
    data += String(BATTERY_1_SOC);
    data += "},";
    data += "{";
    data += "\"voltage\": ";
    data += String(BATTERY_2_VOLTAGE);
    data += ",";
    data += "\"SOC\": ";
    data += String(BATTERY_2_SOC);
    data += "}";
    data += "]";
    data += "}";
    automation.send(200, "text/json", data);
}

void setup() {
    Serial.begin(115200);
    loadVoltages();

    automation.on("/data", handleRequest);
    automation.setup();
    // put your setup code here, to run once:
}

int updateNumber = 0;
long lastUpdate = millis();

int LATEST_VALUES_BAT_1[10];
int LATEST_VALUES_BAT_2[10];

int latestValues[10];

void loop() {
    // put your main code here, to run repeatedly:
    automation.networkLoop();

    if (lastUpdate > millis()) {
        return;
    }
    lastUpdate = millis() + 1000;

    if (updateNumber < 10) {
        LATEST_VALUES_BAT_1[updateNumber] = analogRead(ANALOG_BATTERY_1_PIN);
        // Serial.printf("FIRST %d\n", LATEST_VALUES_BAT_1[updateNumber]);
        LATEST_VALUES_BAT_2[updateNumber] = analogRead(ANALOG_BATTERY_2_PIN);
        // Serial.printf("SECOND %d\n", LATEST_VALUES_BAT_2[updateNumber]);
        updateNumber++;
        return;
    }

    double media_valores_battery_1 = 0.0;
    double media_valores_battery_2 = 0.0;

    for (int i = 0; i < 10; i++) {
        media_valores_battery_1 += LATEST_VALUES_BAT_1[i];
        media_valores_battery_2 += LATEST_VALUES_BAT_2[i];
    }
    media_valores_battery_1 = media_valores_battery_1 / 10;
    media_valores_battery_2 = media_valores_battery_2 / 10;

    double battery_1_voltage_value = calculate_adc_voltage(media_valores_battery_1);
    BATTERY_1_VOLTAGE = battery_1_voltage_value * 5;
    BATTERY_1_SOC = calculate_baterry_soc(BATTERY_1_VOLTAGE);

    double battery_2_voltage_value = calculate_adc_voltage(media_valores_battery_2);
    BATTERY_2_VOLTAGE = battery_2_voltage_value * 5;
    BATTERY_2_SOC = calculate_baterry_soc(BATTERY_2_VOLTAGE);

    updateNumber = 0;
}

double ADC_VOLTAGE[36];
int ADC_VALUES[36];

double BATERRY_SOC[11];
double BATERRY_VOLTAGE[11];

void loadVoltages() {
    ADC_VOLTAGE[0] = 0.333;
    ADC_VALUES[0] = 245;
    ADC_VOLTAGE[1] = 0.360;
    ADC_VALUES[1] = 276;
    ADC_VOLTAGE[2] = 0.452;
    ADC_VALUES[2] = 390;
    ADC_VOLTAGE[3] = 0.460;
    ADC_VALUES[3] = 400;
    ADC_VOLTAGE[4] = 0.554;
    ADC_VALUES[4] = 521;
    ADC_VOLTAGE[5] = 0.622;
    ADC_VALUES[5] = 604;
    ADC_VOLTAGE[6] = 0.726;
    ADC_VALUES[6] = 730;
    ADC_VOLTAGE[7] = 0.750;
    ADC_VALUES[7] = 760;
    ADC_VOLTAGE[8] = 0.829;
    ADC_VALUES[8] = 857;
    ADC_VOLTAGE[9] = 0.846;
    ADC_VALUES[9] = 880;
    ADC_VOLTAGE[10] = 0.943;
    ADC_VALUES[10] = 1000;
    ADC_VOLTAGE[11] = 1.056;
    ADC_VALUES[11] = 1142;
    ADC_VOLTAGE[12] = 1.100;
    ADC_VALUES[12] = 1198;
    ADC_VOLTAGE[13] = 1.142;
    ADC_VALUES[13] = 1252;
    ADC_VOLTAGE[14] = 1.233;
    ADC_VALUES[14] = 1364;
    ADC_VOLTAGE[15] = 1.237;
    ADC_VALUES[15] = 1370;
    ADC_VOLTAGE[16] = 1.385;
    ADC_VALUES[16] = 1556;
    ADC_VOLTAGE[17] = 1.434;
    ADC_VALUES[17] = 1618;
    ADC_VOLTAGE[18] = 1.474;
    ADC_VALUES[18] = 1668;
    ADC_VOLTAGE[19] = 1.549;
    ADC_VALUES[19] = 1758;
    ADC_VOLTAGE[20] = 1.573;
    ADC_VALUES[20] = 1790;
    ADC_VOLTAGE[21] = 1.655;
    ADC_VALUES[21] = 1892;
    ADC_VOLTAGE[22] = 1.729;
    ADC_VALUES[22] = 1980;
    ADC_VOLTAGE[23] = 1.797;
    ADC_VALUES[23] = 2070;
    ADC_VOLTAGE[24] = 1.937;
    ADC_VALUES[24] = 2243;
    ADC_VOLTAGE[25] = 2.025;
    ADC_VALUES[25] = 2350;
    ADC_VOLTAGE[26] = 2.056;
    ADC_VALUES[26] = 2385;
    ADC_VOLTAGE[27] = 2.139;
    ADC_VALUES[27] = 2489;
    ADC_VOLTAGE[28] = 2.185;
    ADC_VALUES[28] = 2545;
    ADC_VOLTAGE[29] = 2.292;
    ADC_VALUES[29] = 2680;
    ADC_VOLTAGE[30] = 2.315;
    ADC_VALUES[30] = 2711;
    ADC_VOLTAGE[31] = 2.396;
    ADC_VALUES[31] = 2815;
    ADC_VOLTAGE[32] = 2.426;
    ADC_VALUES[32] = 2856;
    ADC_VOLTAGE[33] = 2.509;
    ADC_VALUES[33] = 2965;
    ADC_VOLTAGE[34] = 2.530;
    ADC_VALUES[34] = 2995;
    ADC_VOLTAGE[35] = 2.620;
    ADC_VALUES[35] = 3128;

    for (int i = 0; i < 11; i++) {
        BATERRY_SOC[i] = 100 - (i * 10);
    }
    BATERRY_VOLTAGE[0] = 12.7;
    BATERRY_VOLTAGE[1] = 12.5;
    BATERRY_VOLTAGE[2] = 12.42;
    BATERRY_VOLTAGE[3] = 12.32;
    BATERRY_VOLTAGE[4] = 12.2;
    BATERRY_VOLTAGE[5] = 12.06;
    BATERRY_VOLTAGE[6] = 11.9;
    BATERRY_VOLTAGE[7] = 11.75;
    BATERRY_VOLTAGE[8] = 11.58;
    BATERRY_VOLTAGE[9] = 11.31;
    BATERRY_VOLTAGE[10] = 10.5;
}

double calculate_adc_voltage(int adcValue) {
    if (adcValue < 245) {
        return 0.0;
    }

    int best_value_index = 0;
    int lastDiff = 100000;
    for (int i = 0; i < 36; i++) {
        int diff = ADC_VALUES[i] - adcValue;
        if (diff < 0) {
            diff = diff * -1;
        }
        if (diff < lastDiff) {
            lastDiff = diff;
            best_value_index = i;
        }
    }

    if (lastDiff > 400) {
        // Return voltage directly from formula
        return (adcValue * 3.3) / (4095.0);
    }

    double best_voltage = ADC_VOLTAGE[best_value_index];
    double best_adc_value = ADC_VALUES[best_value_index];

    return adcValue * best_voltage / best_adc_value;
}

double calculate_baterry_soc(double baterry_voltage) {
    int best_value_index = 0;
    int lastDiff = 100000;
    for (int i = 0; i < 11; i++) {
        int diff = BATERRY_VOLTAGE[i] - baterry_voltage;
        if (diff < 0) {
            diff = diff * -1;
        }
        if (diff < lastDiff) {
            lastDiff = diff;
            best_value_index = i;
        }
    }

    double best_voltage = BATERRY_VOLTAGE[best_value_index];
    double best_soc = BATERRY_SOC[best_value_index];
    if (best_value_index == 10 && baterry_voltage < best_soc) {
        return 0;
    }

    return baterry_voltage * best_soc / best_voltage;
}