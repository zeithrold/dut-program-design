#include "io.h"
#include "file.h"
#include "util.h"
#include <ctime>
#include <iostream>

#define STAR_LINE cout << "***************************" << endl
#define TIME_DAY 86400
#define TIME_MONTH 2592000;

namespace entry {
    char menu() {
        cout << "Choose the entry menu:" << endl;
        cout << "'r': Register" << endl;
        cout << "'l': Login" << endl;
        cout << "'e': Exit" << endl;
        char result;
        cout << "Your choice > ";
        cin >> result;
        switch (result) {
        case 'r':
        case 'l':
        case 'e':
            break;
        default:
            cout << "Wrong match." << endl;
            result = 0;
        }
        return result;
    }

    People* login(ListNode<People>* p_ln) {
        cout << "Enter your ID to login: ";
        string id;
        cin >> id;
        People* result = find_people_by_id(p_ln, id);
        if (!result) {
            cout << "Cannot find people." << endl;
            return nullptr;
        }
        cout << "Now, enter your password: ";
        string password;
        cin >> password;
        if (result->password != password) {
            cout << "Wrong password." << endl;
            return nullptr;
        }
        return result;
    }

    void reg(ListNode<People>* p_ln) {
        string id;
        string name;
        string email;
        string password;
        string faculty;
        string type = "student";
        string phone_number;
        cout << "Enter ID > ";
        cin >> id;
        if (find_people_by_id(p_ln, id)) {
            cout << "Error: Duplicate id" << endl;
            return;
        }
        cout << "Enter name > ";
        cin >> name;
        cout << "Enter email > ";
        cin >> email;
        cout << "Enter password > ";
        cin >> password;
        cout << "Enter faculty (department also OK) > ";
        cin >> faculty;
        cout << "Enter phone number > ";
        cin >> phone_number;
        auto p = new People(id, name, email, type, phone_number, faculty, password);
        push_back(p_ln, p);
        cout << "Registry complete" << endl;
    }
}

namespace common {
    void display_people_edit_list(bool is_admin) {
        cout << "1. Edit password" << endl;
        cout << "2. Edit email" << endl;
        cout << "3. Edit phone number" << endl;
        if (is_admin) {
            cout << "4. Edit type" << endl;
            cout << "5. Edit faculty" << endl;
        }
        cout << endl << "0. Exit" << endl;
    }

    void display_menu(People* p) {
        STAR_LINE;
        cout << "Welcome, " << p->name << "!" << endl;
        cout << "Here's a list of menu for you." << endl;
        STAR_LINE;
        cout << "Personal Menu:" << endl;
        cout << "1. My Info" << endl;
        cout << "2. My Vaccine Info" << endl;
        cout << "3. My Health Info" << endl;
        cout << "4. My PCR Test Info" << endl;
        cout << "5. Upload My Health Info" << endl;
        cout << "6. Edit My Info" << endl;
        if (p->type == "teacher") {
            cout << endl;
            cout << "Administrator Menu:" << endl;
            cout << "11. Add a People" << endl;
            cout << "12. Show a People" << endl;
            cout << "13. Remove a People" << endl;
            cout << "14. Edit a People" << endl;
            cout << endl;
            cout << "21. Add a PCR Record" << endl;
            cout << "22. Show Recent PCR Record" << endl;
            cout << "23. Show People's PCR Record" << endl;
            cout << endl;
            cout << "31. Show Recent Health Info Record" << endl;
            cout << "32. Show People's Health Info Record" << endl;
            cout << endl;
            cout << "41. Add a Vaccine Record" << endl;
            cout << "42. Show Recent Vaccine Record" << endl;
            cout << "43. Show People's Vaccine Record" << endl;
        }
        cout << endl;
        cout << "0. Exit" << endl;
    }


    time_t judgement_line() {
        STAR_LINE;
        cout << "1. Recent 24 Hours" << endl;
        cout << "2. Yesterday" << endl;
        cout << "3. Recent 3 Days" << endl;
        cout << "4. Recent Month" << endl;
        cout << "Your select: ";
        char select;
        cin >> select;
        long time_length = 0;
        switch (select) {
        case '1':
            time_length = TIME_DAY;
            break;
        case '2':
            time_length = TIME_DAY * 2;
            break;
        case '3':
            time_length = TIME_DAY * 3;
            break;
        case '4':
            time_length = TIME_MONTH;
            break;
        default:
            cout << "No match" << endl;
            return 0;
        }
        auto result = time(nullptr) - time_length;
        return result;
    }

}

namespace people {
    void show(People* p, ListNode<People>* p_ln, ListNode<PCRTestResultInfo>* pcr_ln, ListNode<HealthInfo>* h_ln,
        ListNode<VaccineInfo>* vac_ln) {
        cout << p->name << "'s Info" << endl;
        STAR_LINE;
        cout << "ID: " << p->id << endl;
        cout << "Type: " << p->type << endl;
        cout << "Faculty: " << p->faculty << endl;
        cout << "Phone Number: " << p->phone_number << endl;
        cout << "Email: " << p->email << endl;
        STAR_LINE;
        cout << "Recent PCR Test Result: " << endl;
        auto work_pcr_ln = pcr_ln;
        ListNode<PCRTestResultInfo>* recent_pcr_ln = nullptr;
        sort(work_pcr_ln);
        while (work_pcr_ln) {
            if (work_pcr_ln->data->id == p->id) {
                recent_pcr_ln = work_pcr_ln;
            }
            work_pcr_ln = work_pcr_ln->next;
        }
        if (!recent_pcr_ln) {
            cout << "No PCR Test result under the name of " << p->name << "." << endl;
        }
        else {
            cout << "Time: " << convert_to_local_time(recent_pcr_ln->data->date) << endl;
            cout << "Result: " << (recent_pcr_ln->data->is_positive ? "POSITIVE" : "NEGATIVE") << endl;
            cout << "Execute Location: " << recent_pcr_ln->data->execute_location << endl;
        }
        health::show_people_simplified(h_ln, p->id);
        vac::show_people_simplified(vac_ln, p->id);
    }

    void add(ListNode<People>* p_ln) {
        entry::reg(p_ln);
    }

    void show(ListNode<People>* p_ln, ListNode<PCRTestResultInfo>* pcr_ln, ListNode<HealthInfo>* h_ln,
        ListNode<VaccineInfo>* vac_ln) {
        vector<People*> p;
        string name;
        cout << "Enter Name: ";
        cin >> name;
        if ((p = find_people_by_name(p_ln, name)).empty()) {
            cout << "Cannot find People" << endl;
            return;
        }
        if (p.size() == 1) {
            show(p.front(), p_ln, pcr_ln, h_ln, vac_ln);
        }
        else {
            cout << "Choose one: " << endl;
            int i = 0;
            for (const auto& item : p) {
                ++i;
                cout << i << ". " << item->name << "(" << item->id << ")" << endl;
            }
            string selection;
            cout << "Your selection: ";
            cin >> selection;
            int selection_number = atoi(selection.c_str());
            show(p[selection_number - 1], p_ln, pcr_ln, h_ln, vac_ln);
        }
    }

    void remove(ListNode<People>* p_ln) {
        string id;
        cout << "Enter the id you want to remove: ";
        cin >> id;
        People* p;
        if (!(p = find_people_by_id(p_ln, id))) {
            cout << "Not found" << endl;
            return;
        }
        auto work_ln = p_ln;
        if (work_ln->data->id == p->id) {
            auto temp_ln = p_ln->next->next;
            p_ln->data = p_ln->next->data;
            free(p_ln->next);
            p_ln->next = temp_ln;
            return;
        }
        auto previous_ln = work_ln;
        work_ln = work_ln->next;
        while (work_ln) {
            if (work_ln->data->id == p->id) {
                previous_ln->next = work_ln->next;
                free(work_ln);
                return;
            }
            previous_ln = work_ln;
            work_ln = work_ln->next;
        }
    }

    void edit(People* p, bool is_admin) {
        common::display_people_edit_list(is_admin);
        cout << "Your choice > ";
        char choose;
        cin >> choose;
        switch (choose) {
        case '1': // passwd
        {
            cout << "Enter the password > ";
            string password;
            cin >> password;
            p->password = password;
            break;
        }
        case '2': // email
        {
            cout << "Enter the email > ";
            string email;
            cin >> email;
            p->email = email;
            break;
        }
        case '3': // phone number
        {
            cout << "Enter the phone number > ";
            string phone_number;
            cin >> phone_number;
            p->phone_number = phone_number;
            break;
        }
        case '4': // type
        {
            if (!is_admin) {
                cerr << "You don't have permission to access" << endl;
                return;
            }
            if (p->type == "student") {
                cout << p->name << "'s name is STUDENT, change to TEACHER?(y) ";
                char choice;
                cin >> choice;
                if (choice == 'y') {
                    p->type = "teacher";
                }
            }
            else {
                cout << p->name << "'s name is TEACHER, change to STUDENT?(y) ";
                char choice;
                cin >> choice;
                if (choice == 'y') {
                    p->type = "student";
                }
            }
            break;
        }
        case '5': // faculty
        {
            if (!is_admin) {
                cerr << "You don't have permission to access" << endl;
                return;
            }
            cout << "Enter the faculty (department also OK) " << endl;
            string faculty;
            cin >> faculty;
            p->faculty = faculty;
            break;
        }
        case '0':
            break;
        default: {
            cout << "Not match" << endl;
            break;
        }
        }
    }

    void edit(ListNode<People>* p_ln) {
        string id;
        cout << "Enter the id you want to edit: ";
        cin >> id;
        People* p;
        if (!(p = find_people_by_id(p_ln, id))) {
            cout << "Not found" << endl;
            return;
        }
        edit(p, true);
    }

}

namespace vac {
    int show_people(ListNode<VaccineInfo>* vac_ln, string id) {
        STAR_LINE;
        cout << "Recent Vaccine Injection Info" << endl;
        auto work_vac_ln = vac_ln;
        int vac_times = 0;
        cout << "Time\tInject Times\tType" << endl;
        while (work_vac_ln) {
            if (work_vac_ln->data->id == id) {
                vac_times++;
                cout << convert_to_local_time(work_vac_ln->data->date) << "\t" << work_vac_ln->data->time << "\t"
                    << work_vac_ln->data->type << endl;
            }
            work_vac_ln = work_vac_ln->next;
        }
        if (!vac_times) {
            cout << "No Info!" << endl;
        }
        cout << "Vaccine inject times: " << vac_times << endl;
        return vac_times;
    }

    void show_people_simplified(ListNode<VaccineInfo>* vac_ln, string id) {
        STAR_LINE;
        auto work_vac_ln = vac_ln;
        int vac_times = 0;
        while (work_vac_ln) {
            if (work_vac_ln->data->id == id) {
                vac_times++;
            }
            work_vac_ln = work_vac_ln->next;
        }
        cout << "Vaccine inject times: " << vac_times << endl;
    }

    void add(ListNode<People>* p_ln, ListNode<VaccineInfo>* vac_ln) {
        cout << "Enter a people's id > ";
        string id;
        cin >> id;
        People* p = find_people_by_id(p_ln, id);
        if (!p) {
            cout << "No matches!" << endl;
            return;
        }
        int times = show_people(vac_ln, p->id);
        times++;
        string type;
        if (times > 1) {
            cout << "It has already injected vaccine at least once." << endl;
            cout << "Therefore, the other injection must be the same type." << endl;
            auto work_ln = vac_ln;
            while (work_ln) {
                if (vac_ln->data->id == id) {
                    type = vac_ln->data->type;
                }
                work_ln = work_ln->next;
            }
            cout << "Injected? (y) > ";
            char choose;
            cin >> choose;
            if (choose != 'y') {
                return;
            }
            auto info_raw = (VaccineInfo*)malloc(sizeof(VaccineInfo));
            auto info = new(info_raw) VaccineInfo;
            info->type = type;
            info->id = id;
            info->time = times;
            info->date = time(nullptr);
            push_back<VaccineInfo>(vac_ln, info);
        }
        else {
            cout << "Choose the proper vaccine." << endl;
            cout << "1. SINOVAC" << endl;
            cout << "2. BJBPI" << endl;
            cout << "3. ZFSW" << endl;
            cout << "4. CanSinoBIO" << endl;
            cout << "Your select > ";
            char choose;
            cin >> choose;
            auto info_raw = (VaccineInfo*)malloc(sizeof(VaccineInfo));
            auto info = new(info_raw) VaccineInfo;
            switch (choose) {
            case '1':
                info->type = "SINOVAC";
                break;
            case '2':
                info->type = "BJBPI";
                break;
            case '3':
                info->type = "ZFSW";
                break;
            case '4':
                info->type = "CanSinoBIO";
                break;
            default:
                cout << "Not Found!" << endl;
                return;
            }
            info->time = times;
            info->date = time(nullptr);
            info->id = p->id;
            cout << "Injected? (y) > ";
            char choose_inject;
            cin >> choose_inject;
            if (choose_inject != 'y') {
                return;
            }
            push_back<VaccineInfo>(vac_ln, info);
        }
    }
    void show_recent(ListNode<VaccineInfo>* vac_ln, ListNode<People>* p_ln) {
        auto jl = common::judgement_line();
        if (!jl) {
            return;
        }
        sort(vac_ln);
        auto work_ln = vac_ln;
        cout << "Name\tDate\tType\tInjectTime" << endl;
        work_ln = work_ln->next;
        bool has_data = false;
        while (work_ln) {
            if (work_ln->data->date > jl) {
                has_data = true;
                People* p = find_people_by_id(p_ln, work_ln->data->id);
                cout << p->name << "\t"
                    << convert_to_local_time(work_ln->data->date) << "\t"
                    << work_ln->data->type << "\t"
                    << work_ln->data->time << endl;
            }
            work_ln = work_ln->next;
        }
        if (!has_data) {
            cout << "No data!" << endl;
        }
    }
    void show_people(ListNode<VaccineInfo>* vac_ln, ListNode<People>* p_ln) {
        cout << "Enter a people's id > ";
        string id;
        cin >> id;
        People* p = find_people_by_id(p_ln, id);
        if (!p) {
            cout << "No matches!" << endl;
            return;
        }
        show_people(vac_ln, p->id);
    }
}

namespace health {
    void show_recent(ListNode<HealthInfo>* h_ln, ListNode<People>* p_ln) {
        auto jl = common::judgement_line();
        if (!jl) {
            return;
        }
        sort(h_ln);
        auto work_ln = h_ln;
        cout << "Name\tDate\tCOVID19-related symptom\tTemperature" << endl;
        work_ln = work_ln->next;
        bool has_data = false;
        while (work_ln) {
            if (work_ln->data->date > jl) {
                has_data = true;
                People* p = find_people_by_id(p_ln, work_ln->data->id);
                cout << p->name << "\t" << convert_to_local_time(work_ln->data->date) << "\t"
                    << (work_ln->data->covid19_related_symptom ? "YES" : "NO") << "\t";
                printf("%.2f\n", work_ln->data->temperature);
            }
            work_ln = work_ln->next;
        }
        if (!has_data) {
            cout << "No data!" << endl;
        }
    }
    void show_people(ListNode<HealthInfo>* h_ln, ListNode<People>* p_ln) {
        cout << "Enter a people's id > ";
        string id;
        cin >> id;
        People* p = find_people_by_id(p_ln, id);
        if (!p) {
            cout << "No matches!" << endl;
            return;
        }
        show_people(h_ln, p->id);
    }
    void show_people(ListNode<HealthInfo>* h_ln, string id) {
        STAR_LINE;
        cout << "Recent health report: " << endl;
        auto work_h_ln = h_ln;
        cout << "Time\tCOVID19-related symptom\tTemperature" << endl;
        bool found = false;
        while (work_h_ln) {
            if (work_h_ln->data->id == id) {
                found = true;
                cout << convert_to_local_time(work_h_ln->data->date) << "\t"
                    << (work_h_ln->data->covid19_related_symptom ? "YES" : "NO") << "\t";
                printf("%.2f\n", work_h_ln->data->temperature);
            }
            work_h_ln = work_h_ln->next;
        }
        if (!found) {
            cout << "No health report." << endl;
        }
    }

    void show_people_simplified(ListNode<HealthInfo>* h_ln, string id) {
        STAR_LINE;
        cout << "Recent health report: " << endl;
        auto work_h_ln = h_ln;
        ListNode<HealthInfo>* recent_h_ln = nullptr;
        while (work_h_ln) {
            if (work_h_ln->data->id == id) {
                recent_h_ln = work_h_ln;
            }
            work_h_ln = work_h_ln->next;
        }
        if (!recent_h_ln) {
            cout << "No health report." << endl;
        }
        else {
            cout << "Time: " << convert_to_local_time(recent_h_ln->data->date) << endl;
            cout << "COVID19-related symptom: " << (recent_h_ln->data->covid19_related_symptom ? "YES" : "NO") << endl;
            cout << "Temperature: ";
            printf("%.2f\n", recent_h_ln->data->temperature); // Temperature Formatted Output
        }
    }
}

namespace pcr {
    void add(ListNode<PCRTestResultInfo>* pcr_ln, ListNode<People>* p_ln) {
        auto info_raw = (PCRTestResultInfo*)malloc(sizeof(PCRTestResultInfo));
        auto info = new(info_raw) PCRTestResultInfo;
        cout << "Enter ID: ";
        cin >> info->id;
        if (!find_people_by_id(p_ln, info->id)) {
            cout << "Cannot find ID" << endl;
            return;
        }
        cout << "Enter PCR Test Result, ('POSITIVE' or 'NEGATIVE'): ";
        string pcr_result_text;
        cin >> pcr_result_text;
        if (pcr_result_text == "POSITIVE") {
            info->is_positive = true;
        }
        else if (pcr_result_text == "NEGATIVE") {
            info->is_positive = false;
        }
        else {
            cout << "Not match" << endl;
            return;
        }
        cout << "Enter PCR Test execution place: ";
        cin >> info->execute_location;
        info->date = (int)time(nullptr);
        push_back<PCRTestResultInfo>(pcr_ln, info);
    }

    void show_recent(ListNode<PCRTestResultInfo>* pcr_ln, ListNode<People>* p_ln) {
        auto jl = common::judgement_line();
        if (!jl) {
            return;
        }
        sort(pcr_ln);
        auto work_ln = pcr_ln;
        cout << "Name\tDate\tExeLocation\tResult" << endl;
        bool has_data = false;
        while (work_ln) {
            if (work_ln->data->date > jl) {
                has_data = true;
                People* p = find_people_by_id(p_ln, work_ln->data->id);
                cout << p->name << "\t"
                    << convert_to_local_time(work_ln->data->date) << "\t"
                    << work_ln->data->execute_location << "\t"
                    << (work_ln->data->is_positive ? "POSITIVE" : "NEGATIVE") << endl;
            }
            work_ln = work_ln->next;
        }
        if (!has_data) {
            cout << "No data!" << endl;
        }
    }

    void show_people(ListNode<PCRTestResultInfo>* pcr_ln, ListNode<People>* p_ln) {
        cout << "Enter a people's id > ";
        string id;
        cin >> id;
        People* p = find_people_by_id(p_ln, id);
        if (!p) {
            cout << "No matches!" << endl;
            return;
        }
        show_people(pcr_ln, p->id);
    }

    void show_people(ListNode<PCRTestResultInfo>* pcr_ln, string id) {
        STAR_LINE;
        bool found = false;
        auto work_ln = pcr_ln;
        cout << id << "'s PCR test result records" << endl;
        cout << "Date\tExeLocation\tResult" << endl;
        while (work_ln) {
            if (work_ln->data->id == id) {
                found = true;
                cout << convert_to_local_time(work_ln->data->date) << "\t"
                    << work_ln->data->execute_location << "\t"
                    << (work_ln->data->is_positive ? "POSITIVE" : "NEGATIVE") << endl;
            }
            work_ln = work_ln->next;
        }
        if (!found) {
            cout << "No record found" << endl;
        }
    }
}

namespace personal {
    void my_info(People* p, ListNode<People>* p_ln, ListNode<PCRTestResultInfo>* pcr_ln, ListNode<HealthInfo>* h_ln,
        ListNode<VaccineInfo>* vac_ln) {
        people::show(p, p_ln, pcr_ln, h_ln, vac_ln);
    }

    void edit_my_info(People* p) {
        people::edit(p, p->type == "teacher");
    }

    void my_vaccine_info(People* p, ListNode<VaccineInfo>* vac_ln) {
        vac::show_people(vac_ln, p->id);
    }

    void my_health_info(People* p, ListNode<HealthInfo>* h_ln) {
        health::show_people(h_ln, p->id);
    }

    void my_pcr_test_info(People* p, ListNode<PCRTestResultInfo>* pcr_ln) {
        pcr::show_people(pcr_ln, p->id);
    }

    void upload_my_health_info(People* p, ListNode<HealthInfo>* h_ln) {
        auto info_raw = (HealthInfo*)malloc(sizeof(HealthInfo));
        auto info = new(info_raw) HealthInfo;
        cout << "Have you ever have COVID-19-related symptom? (y) ";
        char choose;
        cin >> choose;
        info->covid19_related_symptom = choose == 'y';
        cout << "Enter your temperature: ";
        string text_temperature;
        cin >> text_temperature;
        info->temperature = atof(text_temperature.c_str());
        info->date = time(nullptr);
        info->id = p->id;
        push_back<HealthInfo>(h_ln, info);
    }
}

void start() {
    ListNode<People>* p_ln = from_text_line<People>(read_file("people.csv"));
    ListNode<PCRTestResultInfo>* pcr_ln = from_text_line<PCRTestResultInfo>(read_file("pcr_test_result_info.csv"));
    ListNode<HealthInfo>* h_ln = from_text_line<HealthInfo>(read_file("health_info.csv"));
    ListNode<VaccineInfo>* vac_ln = from_text_line<VaccineInfo>(read_file("vaccine_info.csv"));
    char menu;
    People* op;
    while ((menu = entry::menu()) != 'e') {
        switch (menu) {
        case 'r':
            entry::reg(p_ln);
            break;
        case 'l':
            op = entry::login(p_ln);
            break;
        default:
            break;
        }
        if (menu == 'l') {
            if (!op) {
                continue;
            }
            bool quit = false;
            while (!quit) {
                quit = false;
                common::display_menu(op);
                cout << "Enter your select: ";
                string selection_text;
                cin >> selection_text;
                int selection = atoi(selection_text.c_str());
                switch (selection) {
                case 1:
                    personal::my_info(op, p_ln, pcr_ln, h_ln, vac_ln);
                    break;
                case 2:
                    personal::my_vaccine_info(op, vac_ln);
                    break;
                case 3:
                    personal::my_health_info(op, h_ln);
                    break;
                case 4:
                    personal::my_pcr_test_info(op, pcr_ln);
                    break;
                case 5:
                    personal::upload_my_health_info(op, h_ln);
                    break;
                case 6:
                    personal::edit_my_info(op);
                    break;
                case 11:
                    people::add(p_ln);
                    break;
                case 12:
                    people::show(p_ln, pcr_ln, h_ln, vac_ln);
                    break;
                case 13:
                    people::remove(p_ln);
                    break;
                case 14:
                    people::edit(p_ln);
                    break;
                case 21:
                    pcr::add(pcr_ln, p_ln);
                    break;
                case 22:
                    pcr::show_recent(pcr_ln, p_ln);
                    break;
                case 23:
                    pcr::show_people(pcr_ln, p_ln);
                    break;
                case 31:
                    health::show_recent(h_ln, p_ln);
                    break;
                case 32:
                    health::show_people(h_ln, p_ln);
                    break;
                case 41:
                    vac::add(p_ln, vac_ln);
                    break;
                case 42:
                    vac::show_recent(vac_ln, p_ln);
                    break;
                case 43:
                    vac::show_people(vac_ln, p_ln);
                    break;
                default:
                    quit = true;
                    break;
                }
            }
        }
    }

    cout << "Saving files..." << endl;
    write_file("people.csv", to_text_line(p_ln));
    write_file("pcr_test_result_info.csv", to_text_line(pcr_ln));
    write_file("health_info.csv", to_text_line(h_ln));
    write_file("vaccine_info.csv", to_text_line(vac_ln));
}
