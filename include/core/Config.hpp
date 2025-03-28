#pragma once

#include <string>
#include <unordered_map>
#include <variant>

namespace core {

class Config {
public:
    using Value = std::variant<int, float, std::string, bool>;

    static Config& getInstance() {
        static Config instance;
        return instance;
    }

    void setValue(const std::string& key, const Value& value) {
        m_settings[key] = value;
    }

    template<typename T>
    T getValue(const std::string& key, const T& defaultValue = T()) const {
        auto it = m_settings.find(key);
        if (it != m_settings.end()) {
            if (auto value = std::get_if<T>(&it->second)) {
                return *value;
            }
        }
        return defaultValue;
    }

    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;

private:
    Config() = default;
    std::unordered_map<std::string, Value> m_settings;
};

} // namespace core 