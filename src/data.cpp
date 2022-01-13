#include "data.h"
#include "util.h"
#include <vector>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;

template <> vector<string> to_text_line<People>(ListNode<People>* list_node) {
    ListNode<People>* ln = list_node;
    vector<string> result;
    stringstream ss;
    ss << "id,name,email,type,phone_numer,faculty,password";
    result.push_back(ss.str());
    ss.str("");
    while (ln) {
        ss << ln->data->id << ",";
        ss << ln->data->name << ",";
        ss << ln->data->email << ",";
        ss << ln->data->type << ",";
        ss << ln->data->phone_number << ",";
        ss << ln->data->faculty << ",";
        ss << ln->data->password;
        result.push_back(ss.str());
        ss.str("");
        ln = ln->next;
    }
    return result;
}

template <> vector<string> to_text_line<PCRTestResultInfo>(ListNode<PCRTestResultInfo>* list_node) {
    ListNode<PCRTestResultInfo>* ln = list_node;
    vector<string> result;
    stringstream ss;
    ss << "id,date,execute_location,is_positive";
    result.push_back(ss.str());
    ss.str("");
    while (ln) {
        ss << ln->data->id << ",";
        ss << to_string(ln->data->date) << ",";
        ss << ln->data->execute_location << ",";
        ss << ln->data->is_positive ? "positive" : "negative";
        result.push_back(ss.str());
        ss.str("");
        ln = ln->next;
    }
    return result;
}

template <> vector<string> to_text_line<VaccineInfo>(ListNode<VaccineInfo>* list_node) {
    ListNode<VaccineInfo>* ln = list_node;
    vector<string> result;
    stringstream ss;
    ss << "id,date,time,type";
    result.push_back(ss.str());
    ss.str("");
    while (ln) {
        ss << ln->data->id << ",";
        ss << to_string(ln->data->date) << ",";
        ss << to_string(ln->data->time) << ",";
        ss << ln->data->type;
        result.push_back(ss.str());
        ss.str("");
        ln = ln->next;
    }
    return result;
}

template <> vector<string> to_text_line<HealthInfo>(ListNode<HealthInfo>* list_node) {
    ListNode<HealthInfo>* ln = list_node;
    vector<string> result;
    stringstream ss;
    ss << "id,date,temperature,covid19_related_symptom";
    result.push_back(ss.str());
    ss.str("");
    while (ln) {
        ss << ln->data->id << ",";
        ss << to_string(ln->data->date) << ",";
        ss << to_string(ln->data->temperature) << ",";
        ss << ln->data->covid19_related_symptom ? "positive" : "negative";
        result.push_back(ss.str());
        ss.str("");
        ln = ln->next;
    }
    return result;
}

template <> ListNode<People>* from_text_line<People>(vector<string> text_line) {
    auto ln = (ListNode<People> *)malloc(sizeof(ListNode<People>));
    auto top_ln = ln;
    ListNode<People>* previous = nullptr;
    for (auto line : text_line) {
        if (!ln) {
            cout << "Failed to malloc" << endl;
            exit(-1);
        }
        vector<string> splited_substr = split_str(line, ",");
        //ln->data = (People*)malloc(sizeof(People));
        auto p_raw = malloc(sizeof(People));
        auto p = new(p_raw) People;
        p->id = splited_substr[0];
        p->name = splited_substr[1];
        p->email = splited_substr[2];
        p->type = splited_substr[3];
        p->phone_number = splited_substr[4];
        p->faculty = splited_substr[5];
        p->password = splited_substr[6];
        ln->data = p;
        ln->next = (ListNode<People> *)malloc(sizeof(ListNode<People>));
        previous = ln;
        ln = ln->next;
    }
    previous->next = nullptr;
    free(ln);
    return top_ln;
}

template <> ListNode<PCRTestResultInfo>* from_text_line<PCRTestResultInfo>(vector<string> text_line) {
    auto ln = (ListNode<PCRTestResultInfo> *)malloc(sizeof(ListNode<PCRTestResultInfo>));
    auto top_ln = ln;
    ListNode<PCRTestResultInfo>* previous = nullptr;
    for (auto line : text_line) {
        if (!ln) {
            cout << "Failed to malloc" << endl;
            exit(-1);
        }
        vector<string> splited_substr = split_str(line, ",");
        auto p_raw = malloc(sizeof(PCRTestResultInfo));
        auto p = new(p_raw) PCRTestResultInfo;
        p->id = splited_substr[0];
        p->date = atol(splited_substr[1].c_str());
        p->execute_location = splited_substr[2];
        p->is_positive = splited_substr[3] == "positive";
        ln->data = p;
        ln->next = (ListNode<PCRTestResultInfo> *)malloc(sizeof(ListNode<PCRTestResultInfo>));
        previous = ln;
        ln = ln->next;
    }
    previous->next = nullptr;
    free(ln);
    return top_ln;
}

template <> ListNode<HealthInfo>* from_text_line<HealthInfo>(vector<string> text_line) {
    auto ln = (ListNode<HealthInfo> *)malloc(sizeof(ListNode<HealthInfo>));
    auto top_ln = ln;
    ListNode<HealthInfo>* previous = nullptr;
    for (auto line : text_line) {
        if (!ln) {
            cout << "Failed to malloc" << endl;
            exit(-1);
        }
        vector<string> splited_substr = split_str(line, ",");
        auto h_raw = malloc(sizeof(HealthInfo));
        auto h = new(h_raw) HealthInfo;
        h->id = splited_substr[0];
        h->date = atol(splited_substr[1].c_str());
        h->temperature = atof(splited_substr[2].c_str());
        h->covid19_related_symptom = splited_substr[3] == "positive";
        ln->data = h;
        ln->next = (ListNode<HealthInfo> *)malloc(sizeof(ListNode<HealthInfo>));
        previous = ln;
        ln = ln->next;
    }
    previous->next = nullptr;
    free(ln);
    return top_ln;
}

template <> ListNode<VaccineInfo>* from_text_line<VaccineInfo>(vector<string> text_line) {
    auto ln = (ListNode<VaccineInfo> *)malloc(sizeof(ListNode<VaccineInfo>));
    auto top_ln = ln;
    ListNode<VaccineInfo>* previous = nullptr;
    for (auto line : text_line) {
        if (!ln) {
            cout << "Failed to malloc" << endl;
            exit(-1);
        }
        vector<string> splited_substr = split_str(line, ",");
        auto v_raw = malloc(sizeof(VaccineInfo));
        auto v = new(v_raw) VaccineInfo;
        v->id = splited_substr[0];
        v->date = atol(splited_substr[1].c_str());
        v->time = atoi(splited_substr[2].c_str());
        v->type = splited_substr[3];
        ln->data = v;
        ln->next = (ListNode<VaccineInfo> *)malloc(sizeof(ListNode<VaccineInfo>));
        previous = ln;
        ln = ln->next;
    }
    previous->next = nullptr;
    free(ln);
    return top_ln;
}

template <> int count<Info>(ListNode<Info>* ln, string id) {
    int result = 0;
    ListNode<Info>* work_ln = ln;
    do {
        if (work_ln->data->id == id) {
            result++;
        }
        work_ln = work_ln->next;
    } while (work_ln);
    return result;
}

People* find_people_by_id(ListNode<People>* p_ln, string id) {
    ListNode<People>* work_ln = p_ln;
    do {
        if (work_ln->data->id == id) {
            break;
        }
        work_ln = work_ln->next;
    } while (work_ln);
    if (work_ln == nullptr) {
        return nullptr;
    }
    return work_ln->data;
}

vector<People*> find_people_by_name(ListNode<People>* p_ln, string name) {
    ListNode<People>* work_ln = p_ln;
    vector<People*> result;
    if (work_ln == nullptr) {
        return result;
    }
    do {
        if (work_ln->data->name == name) {
            result.push_back(work_ln->data);
        }
        work_ln = work_ln->next;
    } while (work_ln);
    return result;
}
