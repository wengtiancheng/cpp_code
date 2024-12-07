#include <string>

class TextEditor {
private:
    std::string leftText;  // 光标左侧的文本
    std::string rightText; // 光标右侧的文本
    std::string clipboard; // 剪贴板，存储复制的文本

public:
    TextEditor();
    void addText(const std::string& text);
    void deleteText(int length);
    void moveCursor(int steps);
    void copy(int length);
    void paste();
    void print();
};