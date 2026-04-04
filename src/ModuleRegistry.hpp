#pragma once

#include <Geode/Geode.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

template <class T>
struct ModuleRegistry : public tinker::utils::Singleton<ModuleRegistry<T>> {
    std::vector<std::function<std::shared_ptr<T>()>> m_modules;
    StringMap<std::vector<std::shared_ptr<Hook>>> m_hooks;
};