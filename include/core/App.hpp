#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <chrono>
#include "Config.hpp"
#include "Logger.hpp"

namespace core {

class App {
public:
    App() = default;
    ~App() = default;

    // Delete copy constructor and assignment operator
    App(const App&) = delete;
    App& operator=(const App&) = delete;

    // Allow move operations
    App(App&&) noexcept = default;
    App& operator=(App&&) noexcept = default;

    void initialize() {
        LOG_INFO("Initializing application...");
        
        // Load configuration
        Config::getInstance().loadFromFile("config.json");
        
        // Setup logging
        Logger::getInstance().setLogFile("app.log");
        
        // Get application name from config or use default
        m_name = Config::getInstance().getValue<std::string>("app.name", "ProfessionalCppProject");
        
        LOG_INFO("Application initialized successfully");
    }

    void run() {
        LOG_INFO("Running application: " + m_name);
        
        // Example of using configuration
        bool debugMode = Config::getInstance().getValue<bool>("app.debug", false);
        if (debugMode) {
            LOG_DEBUG("Debug mode is enabled");
        }
        
        // Main application loop
        auto startTime = std::chrono::steady_clock::now();
        
        // Add your main application logic here
        for (int i = 0; i < 5; ++i) {
            LOG_INFO("Processing iteration " + std::to_string(i + 1));
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        
        auto endTime = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        LOG_INFO("Application ran for " + std::to_string(duration.count()) + "ms");
    }

    void shutdown() {
        LOG_INFO("Shutting down application...");
        
        // Save configuration
        Config::getInstance().saveToFile("config.json");
        
        LOG_INFO("Application shutdown complete");
    }

private:
    std::string m_name{"ProfessionalCppProject"};
};

} // namespace core 