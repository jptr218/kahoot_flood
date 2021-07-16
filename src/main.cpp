#include "hdr.h"

void join(string pin, string name) {
    uint64_t t = chrono::duration_cast<std::chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    string res = exec("curl -i -s https://kahoot.it/reserve/session/" + pin + "/?" + to_string(t));
    string stok;
    string ctok;

    if (res.find("Not found", 0) != string::npos) {
        cout << endl << "We couldn't find a game with that PIN." << endl;
        exit(0);
    }

    stok = res.substr(res.find("x-kahoot-session-token") + 24, 129);
    int cstart = res.find("\"challenge\":\"") + 13;
    ctok = solve_challenge(res.substr(cstart, res.length() - 2 - cstart));

    string sid = gen_sid(stok, ctok);
    string handshake = "{\"advice\":{\"timeout\":\"60000\",\"interval\":\"0\"},\"version\":\"1.0\",\"minimumVersion\":\"1.0\",\"channel\":\"/meta/handshake\"}";
    res = exec("curl -s -d \"" + handshake + "\" -X POST https://kahoot.it/cometd/" + pin + "/" + sid + "/handshake");
    string cid = res.substr(res.find("clientId\":\""), 17);

    string name_pl = "{\"channel\": \"/service/controller\", \"clientId\": " + sid + ", \"data\": {\"gameid\": pin, \"host\": \"kahoot.it\", \"name\": " + name + ", \"type\": \"login\"}, \"id\": \"14\"}";
    exec("curl -s -d \"" + handshake + "\" -X POST https://kahoot.it/cometd/" + pin + "/" + sid + "/handshake");
}

int main() {
    string pin;
    string prefix;
    int amount;

    cout << "Game PIN: ";
    cin >> pin;
    cout << endl << "Bot prefix: ";
    cin >> prefix;
    cout << endl << "Amount of bots: ";
    cin >> amount;

    for (int i = 0; i < amount; i++) {
        join(pin, prefix + to_string(i));
    }

    return 1;
}