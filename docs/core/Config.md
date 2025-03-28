# Configuration System Documentation

## Overview

The configuration system provides a flexible and type-safe way to manage application settings. It uses the Singleton pattern to ensure a single source of truth for configuration values and supports multiple data types through `std::variant`.

## Implementation Details

### Value Types

The configuration system supports the following value types:
```cpp
using Value = std::variant<int, float, std::string, bool>;
```

### Key Features

1. **Type Safety**
   - Uses `std::variant` for type-safe value storage
   - Template-based value retrieval with type checking
   - Compile-time type safety

2. **Default Values**
   - All get operations support default values
   - Type-specific default value handling
   - Safe fallback for missing keys

3. **File Persistence**
   - JSON-based configuration storage
   - Automatic file loading and saving
   - Error handling for file operations

## API Reference

### Methods

#### getInstance()
```cpp
static Config& getInstance()
```
Returns the singleton instance of the configuration system.

#### setValue()
```cpp
void setValue(const std::string& key, const Value& value)
```
Sets a configuration value with the specified key.

#### getValue()
```cpp
template<typename T>
T getValue(const std::string& key, const T& defaultValue = T()) const
```
Retrieves a configuration value with type checking and default value support.

#### loadFromFile()
```cpp
void loadFromFile(const std::string& filename)
```
Loads configuration from a JSON file.

#### saveToFile()
```cpp
void saveToFile(const std::string& filename) const
```
Saves the current configuration to a JSON file.

## Usage Examples

### Basic Usage
```cpp
auto& config = Config::getInstance();

// Set values
config.setValue("app.name", std::string("MyApp"));
config.setValue("app.version", 1.0f);
config.setValue("app.debug", true);

// Get values with defaults
std::string name = config.getValue<std::string>("app.name", "DefaultApp");
float version = config.getValue<float>("app.version", 0.0f);
bool debug = config.getValue<bool>("app.debug", false);
```

### File Operations
```cpp
// Load configuration
config.loadFromFile("config.json");

// Modify configuration
config.setValue("app.name", std::string("NewApp"));

// Save changes
config.saveToFile("config.json");
```

### Error Handling
```cpp
try {
    config.loadFromFile("config.json");
} catch (const std::exception& e) {
    LOG_ERROR("Failed to load configuration: " + std::string(e.what()));
    // Use default values
}
```

## JSON Format

The configuration system uses a simple JSON format for file storage:

```json
{
    "app.name": "MyApp",
    "app.version": 1.0,
    "app.debug": true,
    "database.host": "localhost",
    "database.port": 5432
}
```

### Naming Conventions

- Use dot notation for hierarchical keys
- Use lowercase for key names
- Group related settings with common prefixes
- Use descriptive names that indicate purpose

## Thread Safety

The configuration system is designed to be thread-safe:
- All operations are protected by appropriate synchronization
- Value retrieval is atomic
- File operations are synchronized

## Best Practices

1. **Key Naming**
   - Use meaningful, descriptive names
   - Follow a consistent naming convention
   - Use namespacing to avoid conflicts

2. **Default Values**
   - Always provide sensible defaults
   - Document default values
   - Consider environment-specific defaults

3. **File Management**
   - Use appropriate file permissions
   - Implement backup mechanisms
   - Handle file I/O errors gracefully

4. **Type Safety**
   - Use appropriate types for values
   - Avoid type conversions when possible
   - Document type requirements

## Performance Considerations

1. **Memory Usage**
   - Values are stored in memory
   - Consider memory impact of large configurations
   - Implement cleanup mechanisms if needed

2. **File I/O**
   - File operations are buffered
   - Load operations are cached
   - Save operations are atomic

3. **Thread Safety**
   - Minimal locking overhead
   - Efficient synchronization primitives
   - Optimized for concurrent access

## Error Handling

The configuration system implements comprehensive error handling:

1. **File Operations**
   - File not found
   - Permission denied
   - Invalid JSON format
   - Disk space issues

2. **Value Operations**
   - Type mismatch
   - Missing keys
   - Invalid values

3. **Recovery Mechanisms**
   - Fallback to defaults
   - Automatic retry
   - Error logging

## Integration with Other Components

The configuration system is designed to work seamlessly with:

1. **Logging System**
   - Log level configuration
   - File path settings
   - Output format settings

2. **Application Core**
   - Application name
   - Version information
   - Debug settings

3. **External Systems**
   - Database connections
   - API endpoints
   - Service configurations 