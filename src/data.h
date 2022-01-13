#include <vector>
#include <string>

using namespace std;

class People {
public:
    string id; // Example: "20211071410"
    string name;
    string email;
    string type; // "student" or "teacher"
    string phone_number;
    string faculty;
    string password;
    People() {}
    People(string id, string name, string email, string type, string phone_number, string faculty, string password) {
        this->id = id;
        this->name = name;
        this->email = email;
        this->type = type;
        this->phone_number = phone_number;
        this->faculty = faculty;
        this->password = password;
    }
    bool operator < (const People& p) const {
        return this->id < p.id;
    }
    bool operator > (const People& p) const {
        return this->id > p.id;
    }
};

class Info {
public:
    string id;
    long date = 0;
    bool operator < (const Info& p) const {
        return this->date < p.date;
    }
    bool operator > (const Info& p) const {
        return this->date > p.date;
    }
    Info() {}
    Info(string id, long date) {
        this->date = date;
        this->id = id;
    }
};

class PCRTestResultInfo : public Info {
public:
    string execute_location;
    bool is_positive = false;
    PCRTestResultInfo() : Info () {}
    PCRTestResultInfo(string id, long date, string execute_location, bool is_positive) :Info(id, date) {
        this->execute_location = execute_location;
        this->is_positive = is_positive;
    }
};

class VaccineInfo : public Info {
public:
    int time = 0;
    string type;
    VaccineInfo() : Info() {}
    VaccineInfo(string id, long date, int time, string type) :Info(id, date) {
        this->time = time;
        this->type = type;
    }
};

class HealthInfo : public Info {
public:
    float temperature = 0;
    bool covid19_related_symptom = false;
    HealthInfo() : Info () {}
    HealthInfo(string id, long date, float temperature, bool covid19_related_symptom) : Info(id, date) {
        this->temperature = temperature;
        this->covid19_related_symptom = covid19_related_symptom;
    }
};

template<typename T> class ListNode{
public:
    T* data;
    ListNode* next = nullptr;
    bool operator > (const ListNode<T>& t) const {
        return this->data > t.data;
    }
    bool operator < (const ListNode<T>& t) const {
        return this->data < t.data;
    }
};

template <typename T> vector<string> to_text_line(ListNode<T> *list_node);
template <typename T> ListNode<T>* from_text_line(vector<string> text_line);
template <typename T> int count(ListNode<T> *ln, string condition);
template <typename T> void push_back(ListNode<T> *ln, T *t) {
    ListNode<T> *work_pointer = ln;
    auto new_ln = (ListNode<T> *)malloc(sizeof(ListNode<T>));
    new_ln->data = t;
    new_ln->next = nullptr;
    while ((work_pointer = work_pointer->next), work_pointer->next);
    work_pointer->next = new_ln;

}
template <typename T> void sort(ListNode<T> *ln) {
    auto work_ln = ln;
    int amount = 0;
    if (!ln) {
        return;
    }
    while (work_ln) {
        amount++;
        work_ln = work_ln->next;
    }
    work_ln = ln;
    auto* temp_array = (T **)malloc(sizeof(T) * amount);
    for (int i = 0; i < amount; ++i, work_ln = work_ln->next) {
        temp_array[i] = work_ln->data;
    }
    for (int i = 0; i < amount - 1; ++i) {
        int temp_min_index = i;
        for (int j = i + 1; j < amount; ++j) {
            if (*temp_array[j] < *temp_array[temp_min_index]) {
                temp_min_index = j;
            }
        }
        if (temp_min_index == i) {
            continue;
        }
        auto temp = temp_array[temp_min_index];
        temp_array[temp_min_index] = temp_array[i];
        temp_array[i] = temp;
    }
    work_ln = ln;
    for (int i = 0; i < amount; ++i, work_ln = work_ln->next) {
        work_ln->data = temp_array[i];
    }
    free(temp_array);
}

People* find_people_by_id(ListNode<People> *p_ln, string id);
vector<People *> find_people_by_name(ListNode<People> *p_ln, string name);