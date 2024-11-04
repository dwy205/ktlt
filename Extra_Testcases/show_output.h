#include "study_in_pink2.h"


    static void tc_1194() {
        cout << "----- Testcase 194 -----" << endl;

        Configuration * config = new Configuration("./configs/185.txt");
        cout << "Map Num Rows: " << config->map_num_rows << endl;
        cout << "Map Num Cols: " << config->map_num_cols << endl;
        cout << "Max Num Moving Objects: " << config->max_num_moving_objects << endl;
        cout << "Num Wall: " << config->num_walls << endl;
        if (config->num_walls != 0) {
            cout << "Array Wall: " << config->arr_walls->str() << endl;
        }
        cout << "Num Fake Wall: " << config->num_fake_walls << endl;
        if (config->num_fake_walls != 0) {
            cout << "Array Fake Wall: " << config->arr_fake_walls->str() << endl;
        }
        cout << "Shelock Moving Rule: " << config->sherlock_moving_rule << endl;
        cout << "Sherlock init position: " << config->sherlock_init_pos.str() << endl;
        cout << "Sherlock init hp: " << config->sherlock_init_hp << endl;
        cout << "Sherlock init exp: " << config->sherlock_init_exp << endl;
        cout << "Watson Moving Rule: " << config->watson_moving_rule << endl;
        cout << "Watson init position: " << config->watson_init_pos.str() << endl;
        cout << "Watson init hp: " << config->watson_init_hp << endl;
        cout << "Watson init exp: " << config->watson_init_exp << endl;
        cout << "Criminal init position: " << config->criminal_init_pos.str() << endl;
        cout << "Number step: " << config->num_steps << endl;
        delete config;
    }





class TestStudyInPink {
public:
    TestStudyInPink() = default;
    
    static void tc_1194() {
        ::tc_1194();
    }
};

void test() {
    TestStudyInPink::tc_1194();
}