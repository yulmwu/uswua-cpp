#include "html_logger.hpp"
#include "time.hpp"

const std::string log_html = R"(<div class="log-entry-wrapper">
<div class="log-number {kind}">{steps}</div>
<div class="log-entry">
    <div class="timestamp">{date}</div>
    <div class="instruction">
        <b style="margin-right: 10px">Pointer = {pointer}</b> Instruction = <span style="color: #0d6efd;">{opcode}</span> {operand}
    </div>
    <div class="label">Current stack:</div>
    <div class="hexdump">{current_stack}</div>
    <div class="label">Current heap:</div>
    <div class="hexdump">{current_heap}</div>
</div>
</div>)";

const std::string f_html = R"(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="https://fonts.googleapis.com/css2?family=Source+Code+Pro:wght@400;700&display=swap" rel="stylesheet">
    <title>VM Bytecode Execution Log</title>
    <style>
        body {
            font-family: Consolas, monospace;
            background-color: #f8f9fa;
            color: #212529;
            margin: 0;
            padding: 0;
            overflow-x: auto;
            white-space: nowrap;
        }

        .log-container {
            display: inline-block;
            min-width: 900px;
            padding-left: 20px;
            padding-right: 20px;
            padding-bottom: 20px;
        }

        .log-entry-wrapper {
            display: flex;
            margin-bottom: 15px;
        }

        .log-number {
            font-size: 1.2em;
            font-weight: bold;
            margin-right: 15px;
            display: flex;
            align-items: center;
            justify-content: center;
            min-width: 20px;
            width: auto;
            height: 40px;
            border-radius: 8px;
            padding: 0 10px;
            box-shadow: 0 4px 10px rgba(0, 0, 0, 0.2);
        }

        .ok {
            color: #007bff;
            background-color: #f1f3f5;
        }

        .halt {
            color: #000000;
            background-color: #fcd041;
        }

        .error {
            color: #e9ecef;
            background-color: #ff3e3e;
        }

        .log-entry {
            flex: 1;
            margin-bottom: 15px;
            padding: 15px;
            border: 1px solid #dee2e6;
            border-radius: 8px;
            box-shadow: 0 4px 10px rgba(0, 0, 0, 0.1);
            transition: background-color 0.3s ease, box-shadow 0.3s ease;
        }

        .log-entry:hover {
            background-color: #f8f9fa;
            box-shadow: 0 4px 10px rgba(0, 0, 0, 0.3);
        }

        .timestamp {
            font-size: 0.85em;
            color: #868e96;
            margin-bottom: 5px;
        }

        .instruction {
            font-size: 1.2em;
            color: #343a40;
        }

        .label {
            font-size: 1em;
            color: #4e4e4e;
            margin-top: 20px;
        }

        .hexdump {
            font-size: 0.95em;
            background-color: #f1f3f5;
            color: #383a3d;
            padding: 10px 15px;
            border: 1px solid #dee2e6;
            border-radius: 5px;
            overflow-x: auto;
            margin-top: 10px;
            white-space: nowrap;
        }

        hr {
            height: 3px;
            border: 0;
            background-color: rgb(209, 209, 209);
            margin-bottom: 20px;
        }

        @media (max-width: 768px) {
            .log-container {
                min-width: 900px;
            }
        }
    </style>
</head>

<body>
    <div class="log-container">
        <div style="margin-left: 5px; margin-bottom: 15px">
            <h1>Debug Log</h1>
        </div>

        <hr noshade />
        {content}
        <hr noshade />

        <div style="background-color: #000000; color: yellow">Program ended</div>
    </div>
</body>
</html>)";

void replace(std::string& t, std::string s, std::string r) {
    t.replace(t.find(s), s.length(), r);
}

template <typename T>
std::string to_hex_string(T n) {
    std::stringstream ss;
    ss << "0x" << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << static_cast<int>(n);
    return ss.str();
}

void HTMLLogger::write(LogMessage log) {
    std::string result = log_html;
    
    std::string kind;
    if (log.kind == LogKind::OK) kind = "ok";
    if (log.kind == LogKind::ERROR) kind = "error";
    if (log.kind == LogKind::HALT) kind = "halt";
    
    replace(result, "{kind}", kind);
    replace(result, "{steps}", std::to_string(log.steps));
    replace(result, "{date}", current_time());
    replace(result, "{pointer}", to_hex_string(log.pointer));
    replace(result, "{opcode}", to_string(log.op.opcode));
    if (log.op.operand) 
    {
        std::string s = "<span style='color: #333333;'>{operand}</span>";
        replace(s, "{operand}", to_hex_string(log.op.operand.value()));
        replace(result, "{operand}", s);
    } else {
        replace(result, "{operand}", "");
    }
    replace(result, "{current_stack}", log.stack_dump);
    replace(result, "{current_heap}", log.heap_dump);
    
    this->logs.push_back(result);
}

std::string HTMLLogger::html() {
    std::string result = f_html;
    std::string logs;
    for (auto log : this->logs) {
        logs.append(log);
        logs.append("\n");
    }
    replace(result, "{content}", logs);
    return result;
}
