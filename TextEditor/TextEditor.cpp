#include "TextEditor.h"
#include <iostream>

TextEditor::TextEditor() {
    leftText = "";
    rightText = "";
    clipboard = "";
}

void TextEditor::addText(const std::string& text) {
    leftText += text;
}

void TextEditor::deleteText(int length) {
    int deleteLen = std::min(length, (int)leftText.length());
    if (deleteLen > 0) {
        leftText = leftText.substr(0, leftText.length() - deleteLen);
    }
}

void TextEditor::moveCursor(int steps) {
    if (steps > 0) {
        // 向右移动
        int moveLen = std::min(steps, (int)rightText.length());
        leftText += rightText.substr(0, moveLen);
        rightText = rightText.substr(moveLen);
    } else {
        // 向左移动
        int moveLen = std::min(-steps, (int)leftText.length());
        rightText = leftText.substr(leftText.length() - moveLen) + rightText;
        leftText = leftText.substr(0, leftText.length() - moveLen);
    }
}

void TextEditor::copy(int length) {
    int copyLen = std::min(length, (int)leftText.length());
    clipboard = leftText.substr(leftText.length() - copyLen);
}

void TextEditor::paste() {
    if (!clipboard.empty()) {
        leftText += clipboard;
    }
}

void TextEditor::print() {
    std::cout << leftText << rightText << std::endl;
}