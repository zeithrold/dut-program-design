#include "data.h"

using namespace std;

namespace entry {
    char menu();
    People* login(ListNode<People>* p_ln);
    void reg(ListNode<People>* p_ln);
}

namespace personal {
    void my_info(People *p, ListNode<People> *p_ln, ListNode<PCRTestResultInfo> *pcr_ln, ListNode<HealthInfo> *h_ln,
                 ListNode<VaccineInfo> *vac_ln); // Menu 1
    void edit_my_info(People *p); // Menu 6
    void my_vaccine_info(People *p, ListNode<VaccineInfo>* vac_ln); // Menu 2
    void my_health_info(People *p, ListNode<HealthInfo>* h_ln); // Menu 3
    void my_pcr_test_info(People *p, ListNode<PCRTestResultInfo>* pcr_ln); // Menu 4
    void upload_my_health_info(People *p, ListNode<HealthInfo>* h_ln); // Menu 5
}

namespace common {
    void display_people_edit_list(bool is_admin);
    void display_menu(People *p);
    time_t judgement_line();
}

namespace people {
    void add(ListNode<People>* p_ln); // Menu 11
    void show(ListNode<People> *p_ln, ListNode<PCRTestResultInfo> *pcr_ln, ListNode<HealthInfo> *h_ln,
              ListNode<VaccineInfo> *vac_ln); // Menu 12
    void remove(ListNode<People>* p_ln); // Menu 12
    void edit(ListNode<People>* p_ln); // Menu 14
    void edit(People *p, bool is_admin);
    void show(People *p, ListNode<People> *p_ln, ListNode<PCRTestResultInfo> *pcr_ln, ListNode<HealthInfo> *h_ln,
                     ListNode<VaccineInfo> *vac_ln);
}

namespace pcr {
    void add(ListNode<PCRTestResultInfo>* pcr_ln, ListNode<People>* p_ln); // Menu 21
    void show_recent(ListNode<PCRTestResultInfo>* pcr_ln, ListNode<People> *p_ln); // Menu 22
    void show_people(ListNode<PCRTestResultInfo>* pcr_ln, ListNode<People> *p_ln); // Menu 23
    void show_people(ListNode<PCRTestResultInfo>* pcr_ln, string id);
}

namespace vac {
    void add(ListNode<People> *p_ln, ListNode<VaccineInfo> *vac_ln); // Menu 41
    void show_recent(ListNode<VaccineInfo> *vac_ln, ListNode<People> *p_ln); // Menu 42
    void show_people(ListNode<VaccineInfo> *vac_ln, ListNode<People> *p_ln); // Menu 43
    int show_people(ListNode<VaccineInfo>* vac_ln, string id);
    void show_people_simplified(ListNode<VaccineInfo>* vac_ln, string id);
}

namespace health {
    void show_recent(ListNode<HealthInfo> *h_ln, ListNode<People> *p_ln); // Menu 31
    void show_people(ListNode<HealthInfo> *h_ln, ListNode<People> *p_ln); // Menu 32
    void show_people(ListNode<HealthInfo>* h_ln, string id);
    void show_people_simplified(ListNode<HealthInfo>* h_ln, string id);
}

void start();
