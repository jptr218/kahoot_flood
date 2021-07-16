#include "hdr.h"

string exec(string cmd) {
    FILE* pipe = _popen(cmd.c_str(), "r");
    if (!pipe) {
        return "";
    }
    string result;
    char buff[128];
    while (!feof(pipe)) {
        while (fgets(buff, 128, pipe) != NULL) {
            result += buff;
        }
    }
    return result;
}

string b64_dec(string v) {
    string o;
    vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) {
        T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;
    }

    int va = 0;
    int vb = -8;
    for (u_char c : v) {
        if (T[c] == -1) {
            break;
        }
        va = (va << 6) + T[c];
        vb += 6;
        if (vb >= 0) {
            o.push_back(char((va >> vb) & 0xFF));
            vb -= 8;
        }
    }
    return o;
}

string convert_lits(string s) {
    while (1) {
        int o;
        if ((o = s.find("\\u003c")) != -1) {
            s.replace(o, 6, "\u003c");
            continue;
        }
        else if ((o = s.find("\\u003e")) != -1) {
            s.replace(o, 6, "\u003e");
            continue;
        }
        break;
    }
    return s;
}

string runJs(string s) {
    string res = exec("curl -s https://rextester.com/rundotnet/Run -X POST -F \"LanguageChoiceWrapper=17\" -F \"EditorChoiceWrapper=1\" -F \"LayoutChoiceWrapper=1\" -F \"Program=" + s + "\" -F \"Input=\" -F \"Privacy=\" -F \"PrivacyUsers=\" -F \"Title=\" -F \"SavedOutput=\" -F \"WholeError=\" -F \"WholeWarning=\" -F \"StatsToSave=\" -F \"CodeGuid=\" -F \"IsInEditMode=False\" -F \"IsLive=False\"");
    int start = res.find("Result\":\"") + 9;
    int end = res.find("\",\"Stats");
    return res.substr(start, end - start);
}