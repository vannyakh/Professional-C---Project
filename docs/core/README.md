# Core Components Documentation

This document provides detailed information about the core components of the Professional C++ Project.

## Table of Contents
1. [Application Class](#application-class)
2. [Configuration System](#configuration-system)
3. [Logging System](#logging-system)

## Application Class

The `App` class is the main application container that manages the application lifecycle.

### Features
- Singleton pattern implementation
- Thread-safe operations
- Configuration management integration
- Logging system integration
- Performance monitoring

### Usage Example
```cpp
core::App app;
app.initialize();
app.run();
app.shutdown();
```

### Methods
- `initialize()`: Sets up the application, loads configuration, and initializes logging
- `run()`: Executes the main application loop
- `shutdown()`: Performs cleanup and saves configuration

## Configuration System

The `Config` class provides a flexible configuration management system.

### Features
- Singleton pattern implementation
- Type-safe value storage using `std::variant`
- JSON file-based configuration
- Default value support
- Thread-safe operations

### Supported Value Types
- `int`
- `float`
- `std::string`
- `bool`

### Usage Example
```cpp
// Get configuration instance
auto& config = Config::getInstance();

// Set a value
config.setValue("app.name", std::string("MyApp"));

// Get a value with default
std::string appName = config.getValue<std::string>("app.name", "DefaultApp");
bool debugMode = config.getValue<bool>("app.debug", false);

// Load from file
config.loadFromFile("config.json");

// Save to file
config.saveToFile("config.json");
```

### Configuration File Format (JSON)
```json
{
    "app.name": "MyApp",
    "app.debug": true,
    "app.version": 1.0
}
```

## Logging System

The `Logger` class provides a comprehensive logging system.

### Features
- Singleton pattern implementation
- Multiple log levels
- Thread-safe logging
- Console and file output
- Convenient logging macros

### Log Levels
- `Debug`: Detailed information for debugging
- `Info`: General information about application flow
- `Warning`: Warning messages for potential issues
- `Error`: Error messages for critical issues

### Usage Example
```cpp
// Get logger instance
auto& logger = Logger::getInstance();

// Set log file
logger.setLogFile("app.log");

// Using logging macros
LOG_DEBUG("Detailed debug information");
LOG_INFO("General information");
LOG_WARNING("Warning message");
LOG_ERROR("Error message");
```

### Log Format
```
[LEVEL] Message
```

Example:
```
[INFO] Application initialized successfully
[DEBUG] Processing iteration 1
[WARNING] Resource usage above 80%
[ERROR] Failed to connect to database
```

## Thread Safety

All core components are designed with thread safety in mind:
- Configuration system uses atomic operations
- Logging system uses mutex protection
- Application class supports move operations
- All singleton instances are thread-safe

## Best Practices

1. **Configuration**
   - Always provide default values when retrieving configuration
   - Use meaningful key names with proper namespacing
   - Save configuration changes before application shutdown

2. **Logging**
   - Use appropriate log levels
   - Include meaningful context in log messages
   - Set up log file at application startup
   - Use logging macros for consistent formatting

3. **Application Lifecycle**
   - Always call initialize() before run()
   - Call shutdown() to ensure proper cleanup
   - Handle exceptions appropriately

## Dependencies

- C++17 or higher
- Threading support (std::thread)
- JSON parsing (for configuration)
- File I/O operations

## Error Handling

All components implement proper error handling:
- Configuration: Returns default values for missing keys
- Logging: Gracefully handles file I/O errors
- Application: Provides exception-safe operations

## Performance Considerations

- Logging operations are buffered for better performance
- Configuration values are cached in memory
- Thread-safe operations use appropriate synchronization primitives
- Move semantics are supported for efficient resource management 