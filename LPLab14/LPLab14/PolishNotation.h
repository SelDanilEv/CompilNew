#pragma once
#include "pch.h"
#include "LT.h"
#include "IT.h"
#include <iostream>
#include <stack>
#include <queue>

bool polishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable);
int priorityIs(LT::Entry entry);
char intToChar(int x);
//void operatorCase(stack<LT::Entry>& stack, queue<LT::Entry>& queue, LT::LexTable& lextable);