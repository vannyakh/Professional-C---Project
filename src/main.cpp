#include <core/App.hpp>
#include <iostream>

int main() {
    try {
        core::App app;
        
        // Initialize the application
        app.initialize();
        
        // Run the main application loop
        app.run();
        
        // Cleanup and shutdown
        app.shutdown();
        
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown fatal error occurred" << std::endl;
        return 1;
    }
} 