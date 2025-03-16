#include <iostream>
#include <fstream>
#include <string>
#include <regex>

// ��������ȡ�ļ�����
std::string readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "�޷����ļ�: " << filePath << std::endl;
        return "";
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}

// ������д���ļ�����
void writeFile(const std::string& filePath, const std::string& content) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "�޷�д���ļ�: " << filePath << std::endl;
        return;
    }
    file << content;
    file.close();
}

// ���������ͳһ��ʽ�ͷ��ذ�ť
std::string addUniformStyleAndButton(const std::string& htmlContent) {
    // ����ͳһ�� CSS ��ʽ
    std::string style = R"(
        <style>
            /* �������� */
            * {
                margin: 0;
                padding: 0;
                box-sizing: border-box;
            }

            body {
                background: linear-gradient(135deg, #f8f9ff 0%, #e6f0ff 100%);
                min-height: 100vh;
                font-family: 'Inter', sans-serif;
                color: #2c3e50;
                line-height: 1.8;
                padding: 2rem;
            }

            /* �������� */
            #write {
                max-width: 800px;
                margin: 0 auto;
                padding: 2rem;
                background: rgba(255, 255, 255, 0.95);
                border-radius: 16px;
                box-shadow: 0 4px 20px rgba(0, 0, 0, 0.1);
                backdrop-filter: blur(8px);
                border: 1px solid rgba(255, 255, 255, 0.3);
            }

            /* ������ʽ */
            h1, h2, h3 {
                font-family: 'Merriweather', serif;
                font-weight: bold; /* ��Ӵ��� */
                margin-top: 2rem;
                margin-bottom: 1.5rem;
                position: relative;
                padding-bottom: 0.5rem;
            }

            h1 {
                font-size: 2.5rem;
                color: #2c3e50;
                border-bottom: 2px solid #4a90e2;
            }

            h2 {
                font-size: 2rem;
                color: #34495e;
                border-bottom: 1px solid #dfe6e9;
            }

            h3 {
                font-size: 1.5rem;
                color: #4a5568;
            }

            /* ������ʽ */
            p {
                margin: 1.2rem 0;
                font-size: 1.1rem;
                color: #4a5568;
            }

            /* ��ť��ʽ */
            .Button {
                background: linear-gradient(135deg, #4a90e2 0%, #6c5ce7 100%);
                border: none;
                border-radius: 12px;
                color: white;
                padding: 15px 32px;
                text-align: center;
                text-decoration: none;
                display: inline-block;
                font-size: 16px;
                margin: 2rem 0;
                cursor: pointer;
                transition: all 0.3s ease;
                box-shadow: 0 4px 6px rgba(74, 144, 226, 0.2);
            }

            .Button:hover {
                transform: translateY(-2px);
                box-shadow: 0 7px 14px rgba(74, 144, 226, 0.3);
            }

            .Button:active {
                transform: translateY(0);
                box-shadow: 0 4px 6px rgba(74, 144, 226, 0.2);
            }

            /* ��Ӧʽ��� */
            @media (max-width: 768px) {
                body {
                    padding: 1rem;
                }

                #write {
                    padding: 1.5rem;
                }

                h1 {
                    font-size: 2rem;
                }

                h2 {
                    font-size: 1.5rem;
                }

                h3 {
                    font-size: 1.2rem;
                }

                p {
                    font-size: 1rem;
                }
            }

            /* ����Ч�� */
            @keyframes fadeIn {
                from {
                    opacity: 0;
                    transform: translateY(20px);
                }
                to {
                    opacity: 1;
                    transform: translateY(0);
                }
            }

            #write {
                animation: fadeIn 0.8s ease-out;
            }
        </style>
    )";

    // ���巵�ذ�ť�� HTML ����
    std::string backButton = "<div style=\"text-align: center;\">\n<a href=\"javascript:history.back(-1)\">\n<button class=\"Button\">Back to the Previous Page</button>\n</a>\n</div>";

    // �� <head> ��ǩ�в�����ʽ
    std::regex headRegex(R"(<head>(.*?)</head>)", std::regex::icase);
    std::smatch headMatch;
    if (std::regex_search(htmlContent, headMatch, headRegex)) {
        std::string headContent = headMatch.str(0);
        std::string newHeadContent = headMatch.prefix().str() + "<head>" + headMatch.str(1) + style + "</head>" + headMatch.suffix().str();
        return newHeadContent;
    }

    // ���û�� <head> ��ǩ�������һ��
    std::regex htmlRegex(R"(<html(.*?)>(.*?)</html>)", std::regex::icase);
    std::smatch htmlMatch;
    if (std::regex_search(htmlContent, htmlMatch, htmlRegex)) {
        std::string htmlContentWithHead = "<html" + htmlMatch.str(1) + "><head>" + style + "</head>" + htmlMatch.str(2) + "</html>";
        return htmlContentWithHead;
    }

    // ����� <html> ��ǩ��û�У���ֱ�������ʽ
    return "<head>" + style + "</head>" + htmlContent + backButton;
}

int main() {
    // ���������ļ�·��
    std::string inputFile = "AboutDiscreteMathematics.html";  // �滻Ϊ��������ļ�·��
    std::string outputFile = "outputs.html";  // �滻Ϊ�������ļ�·��

    // ��ȡ�����ļ�
    std::string htmlContent = readFile(inputFile);
    if (htmlContent.empty()) {
        std::cerr << "�����ļ�Ϊ�ջ��޷���ȡ��" << std::endl;
        return 1;
    }

    // ���ͳһ��ʽ�ͷ��ذ�ť
    std::string prettifiedHTML = addUniformStyleAndButton(htmlContent);

    // д������ļ�
    writeFile(outputFile, prettifiedHTML);

    std::cout << "HTML ������ɣ�����ļ�: " << outputFile << std::endl;

    return 0;
}
