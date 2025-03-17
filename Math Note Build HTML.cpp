#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string FONT_LINK = R"(
<link href="https://fonts.googleapis.com/css2?family=Inter:wght@400;600&family=Merriweather:wght@400;700&display=swap" rel="stylesheet">
)";

const string CSS_STYLE = R"(
<style>
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

    h1, h2, h3 {
        font-family: 'Merriweather', serif;
        margin-top: 2rem;
        margin-bottom: 1.5rem;
        position: relative;
        padding-bottom: 0.5rem;
    }

    h1 { font-size: 2.5rem; border-bottom: 2px solid #4a90e2; }
    h2 { font-size: 2rem; border-bottom: 1px solid #dfe6e9; }
    h3 { font-size: 1.5rem; color: #4a5568; }

    p {
        margin: 1.2rem 0;
        font-size: 1.1rem;
        color: #4a5568;
    }

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

    @media (max-width: 768px) {
        body { padding: 1rem; }
        #write { padding: 1.5rem; }
        h1 { font-size: 2rem; }
        h2 { font-size: 1.5rem; }
        h3 { font-size: 1.2rem; }
        p { font-size: 1rem; }
    }

    @keyframes fadeIn {
        from { opacity: 0; transform: translateY(20px); }
        to { opacity: 1; transform: translateY(0); }
    }
    #write { animation: fadeIn 0.8s ease-out; }
</style>
)";

string read_file(const string& path) {
    ifstream f(path);
    return string((istreambuf_iterator<char>(f)), 
                 istreambuf_iterator<char>());
}

void write_file(const string& path, const string& content) {
    ofstream f(path);
    f << content;
}

void beautify_html(string& html) {
    // Insert fonts and styles
    size_t head_end = html.find("</head>");
    if (head_end != string::npos) {
        html.insert(head_end, FONT_LINK + CSS_STYLE);
    }

    // Check if the content is already wrapped in <div id="write">
    size_t write_div_start = html.find("<div id=\"write\">");
    size_t write_div_end = html.find("</div>", write_div_start);

    if (write_div_start == string::npos) {
        // If not wrapped, wrap the content
        size_t body_start = html.find("<body");
        if (body_start != string::npos) {
            size_t body_end = html.find(">", body_start);
            size_t content_start = body_end + 1;
            size_t content_end = html.find("</body>", content_start);

            string new_body = string(html.begin() + body_start, html.begin() + content_start) 
                + html.substr(content_start, content_end - content_start)
                + "</div>\n<div style=\"text-align:center\">"
                  "<a href=\"javascript:history.back()\">"
                  "<button class=\"Button\">Back to the Previous Page</button></a></div>"
                + html.substr(content_end);
            
            html.replace(body_start, content_end - body_start + 7, new_body);
        }
    } else {
        // If already wrapped, check if there is a nested <div id="write">
        size_t inner_write_start = html.find("<div id=\"write\">", write_div_end);
        if (inner_write_start != string::npos) {
            // Extract the inner content
            size_t inner_write_end = html.find("</div>", inner_write_start);
            string inner_content = html.substr(inner_write_start + 16, inner_write_end - inner_write_start - 16);

            // Replace the outer <div id="write"> with the inner content
            html.replace(write_div_start, write_div_end - write_div_start + 6, inner_content);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <input.html> <output.html>\n";
        return 1;
    }

    string html = read_file(argv[1]);
    beautify_html(html);
    write_file(argv[2], html);

    cout << "HTML beautified successfully!\n";
    return 0;
}
