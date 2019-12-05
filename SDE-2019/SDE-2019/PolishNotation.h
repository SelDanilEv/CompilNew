#pragma once
#include "pch.h"
#include "LT.h"
#include "IT.h"
#include <iostream>
#include <stack>
#include <queue>

bool polishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable);
LexA::Tables DoPolish(LexA::Tables tables);
char intToChar(int x);

