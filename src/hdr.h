#pragma once
#include <windows.h>
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
using namespace std;

string exec(string cmd);
string b64_dec(string v);
string convert_lits(string s);
string runJs(string s);
string solve_challenge(string s);
string gen_sid(string stok, string ctok);
