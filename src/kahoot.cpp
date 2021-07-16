#include "hdr.h"

string solve_challenge(string s) {
    int i = 0;
    for (char c : s) {
        if ((int)c < 0) {
            s.replace(i, 1, " ");
        }
        else if (c == '\\' && s[i + 1] == 't') {
            s.replace(i, 2, "  ");
        }
        i++;
    }

    s.replace(0, 0, "print(");
    s.replace(s.find("')") + 2, 0, ")");
    s.replace(s.find("if("), s.find("}\\\");") - s.find("if(") + 5, "");
    s.replace(s.find("_", s.find("return")), 1, "message");
    s.replace(s.find("message,"), 8, "");

    s = runJs(s);
    s.replace(s.find("\\n"), 2, "");
    return s;
}

string gen_sid(string stok, string ctok) {
    stok = b64_dec(stok);
    ctok = convert_lits(ctok);

    string o = "";
    int i = 0;
    for (char c : stok) {
        o += c xor ctok[i % ctok.length()];
        i++;
    }
    return o;
}