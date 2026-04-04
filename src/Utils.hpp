#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

namespace tinker::utils {

    template <class T>
    struct FakeClass final {
        alignas(T) std::byte storage[sizeof(T)];

        T* get() noexcept {
            return std::launder(reinterpret_cast<T*>(storage));
        }

        const T* get() const noexcept {
            return std::launder(reinterpret_cast<const T*>(storage));
        }

        T* operator->() noexcept { return get(); }
        const T* operator->() const noexcept { return get(); }

        T& operator*() noexcept { return *get(); }
        const T& operator*() const noexcept { return *get(); }
    };

    template<class T>
    struct Singleton {
        static T* get() {
            static T instance;
            return &instance;
        }
    };

    struct HijackCallback : public CCObject {

        using Hijack = std::function<void(std::function<void(CCObject* sender)> orig, CCObject* sender)>;

        Hijack m_method;
        SEL_MenuHandler m_selector;

        static HijackCallback* create(Hijack method, SEL_MenuHandler originalSelector) {
            auto ret = new HijackCallback();
            if (ret->init(method, originalSelector)) {
                ret->autorelease();
                return ret;
            }
            delete ret;
            return nullptr;
        }

        bool init(Hijack method, SEL_MenuHandler originalSelector) {
            m_method = method;
            m_selector = originalSelector;
            return true;
        }

        void callback(CCObject* sender) {
            auto btn = static_cast<CCMenuItem*>(sender);
            auto hijack = static_cast<HijackCallback*>(btn->getUserObject("hijack"_spr));
            
            if (hijack->m_method) hijack->m_method([btn, hijack] (CCObject* sender) {
                (btn->m_pListener->*hijack->m_selector)(sender);
            }, sender);
        }
    };

    inline void hijackButton(CCMenuItem* btn, HijackCallback::Hijack method) {
        if (btn->getUserObject("hijack"_spr)) return;

        auto hijack = HijackCallback::create(method, btn->m_pfnSelector);
        btn->setUserObject("hijack"_spr, hijack);
        btn->m_pfnSelector = menu_selector(HijackCallback::callback);
    }

    template<geode::utils::string::ConstexprString ID>
    inline Mod* getMod() {
        static auto mod = Loader::get()->getLoadedMod(ID.data());
        return mod;
    }

    inline std::pair<std::string, std::string> splitIntoPair(const std::string& str) {
        auto split = geode::utils::string::split(str, ":");
        auto& key = split[0];
        if (split.size() < 2) return {key, ""};
        auto value = str.substr(key.size() + 1);

        return {key, value};
    }

    inline void forEachObject(GJBaseGameLayer const* game, std::function<void(GameObject*)> const& callback) {
        int count = game->m_sections.empty() ? -1 : game->m_sections.size();
        for (int i = game->m_leftSectionIndex; i <= game->m_rightSectionIndex && i < count; ++i) {
            auto leftSection = game->m_sections[i];
            if (!leftSection) continue;

            auto leftSectionSize = leftSection->size();
            for (int j = game->m_bottomSectionIndex; j <= game->m_topSectionIndex && j < leftSectionSize; ++j) {
                auto section = leftSection->at(j);
                if (!section) continue;

                auto sectionSize = game->m_sectionSizes[i]->at(j);
                for (int k = 0; k < sectionSize; ++k) {
                    auto obj = section->at(k);
                    if (!obj) continue;

                    callback(obj);
                }
            }
        }
    }

    inline CCPoint rotatePointAroundPivot(CCPoint point, CCPoint pivot, float angleDegrees) {
        float angleRadians = CC_DEGREES_TO_RADIANS(angleDegrees);

        float sinA = std::sinf(angleRadians);
        float cosA = std::cosf(angleRadians);

        point.x -= pivot.x;
        point.y -= pivot.y;

        float xNew = point.x * cosA - point.y * sinA;
        float yNew = point.x * sinA + point.y * cosA;

        return CCPoint(xNew + pivot.x, yNew + pivot.y);
    }

    inline CCTouchHandler* findHandler(CCTouchDelegate* delegate) {
        auto mainNode = typeinfo_cast<CCNode*>(delegate);
        for (auto handler : CCArrayExt<CCTouchHandler*>(CCTouchDispatcher::get()->m_pTargetedHandlers)) {
            if (auto node = typeinfo_cast<CCNode*>(handler->getDelegate())) {
                if (mainNode == node) return handler;
            }
        }
        return nullptr;
    }

    inline void collectHandlers(CCNode* node, std::vector<CCTouchHandler*>& out) {
        for (auto child : node->getChildrenExt()) {
            if (auto delegate = typeinfo_cast<CCTouchDelegate*>(child)) {
                if (auto handler = findHandler(delegate)) {
                    out.emplace_back(handler);
                }
            }
            collectHandlers(child, out);
        }
    }

    inline void offsetTouchPrio(CCNode* node, int offset) {
        std::vector<CCTouchHandler*> handlers;
        collectHandlers(node, handlers);

        if (auto delegate = typeinfo_cast<CCTouchDelegate*>(node)) {
            if (auto handler = findHandler(delegate)) {
                handlers.emplace_back(handler);
            }
        }

        for (const auto& handler : handlers) {
            CCTouchDispatcher::get()->setPriority(handler->getPriority() + offset, handler->getDelegate());
        }
    }

    template <geode::utils::string::ConstexprString A, geode::utils::string::ConstexprString B>
    consteval auto concat2() {
        geode::utils::string::ConstexprString<> out{};
        for (size_t i = 0; i < A.size(); ++i)
            out.push(A.data()[i]);
        for (size_t i = 0; i < B.size(); ++i)
            out.push(B.data()[i]);
        return out;
    }

    template <geode::utils::string::ConstexprString First, geode::utils::string::ConstexprString... Rest>
    consteval auto concat() {
        if constexpr (sizeof...(Rest) == 0)
            return First;
        else
            return concat2<First, concat<Rest...>()>();
    }
}

#define $incompatible(modID)                                        \
$execute {                                                      \
    Mod::get()->setSavedValue(modID "-loaded", false);          \
    auto mod = Loader::get()->getInstalledMod(modID);           \
    if (!mod) return;                                           \
    if (mod->isLoaded()) {                                      \
        Mod::get()->setSavedValue(modID "-loaded", true);       \
        return;                                                 \
    }                                                           \
    ModStateEvent(ModEventType::Loaded, mod).listen([]() {      \
        Mod::get()->setSavedValue(modID "-loaded", true);       \
    }).leak();                                                  \
}