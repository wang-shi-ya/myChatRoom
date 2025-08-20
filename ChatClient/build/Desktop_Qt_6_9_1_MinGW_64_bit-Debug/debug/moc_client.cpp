/****************************************************************************
** Meta object code from reading C++ file 'client.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../ChatRoom-main/ChatRoom-main/ChatClient/client.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN6ClientE_t {};
} // unnamed namespace

template <> constexpr inline auto Client::qt_create_metaobjectdata<qt_meta_tag_ZN6ClientE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Client",
        "connected",
        "",
        "disconnected",
        "loginSuccess",
        "account",
        "username",
        "loginFailed",
        "error",
        "registerSuccess",
        "registerFailed",
        "usernameUpdated",
        "newUsername",
        "usernameUpdateFailed",
        "passwordUpdated",
        "passwordUpdateFailed",
        "newMessage",
        "sender",
        "content",
        "isImage",
        "timestamp",
        "target",
        "userOnline",
        "userOffline",
        "onlineUsersReceived",
        "QList<std::pair<int,QString>>",
        "users",
        "historyReceived",
        "messages",
        "forcedLogout",
        "reason",
        "readyRead",
        "onConnected",
        "onDisconnected"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'connected'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'disconnected'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'loginSuccess'
        QtMocHelpers::SignalData<void(int, const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 5 }, { QMetaType::QString, 6 },
        }}),
        // Signal 'loginFailed'
        QtMocHelpers::SignalData<void(const QString &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 },
        }}),
        // Signal 'registerSuccess'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'registerFailed'
        QtMocHelpers::SignalData<void(const QString &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 },
        }}),
        // Signal 'usernameUpdated'
        QtMocHelpers::SignalData<void(const QString &)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 12 },
        }}),
        // Signal 'usernameUpdateFailed'
        QtMocHelpers::SignalData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'passwordUpdated'
        QtMocHelpers::SignalData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'passwordUpdateFailed'
        QtMocHelpers::SignalData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'newMessage'
        QtMocHelpers::SignalData<void(int, const QString &, const QString &, bool, const QString &, int)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 17 }, { QMetaType::QString, 6 }, { QMetaType::QString, 18 }, { QMetaType::Bool, 19 },
            { QMetaType::QString, 20 }, { QMetaType::Int, 21 },
        }}),
        // Signal 'userOnline'
        QtMocHelpers::SignalData<void(int, const QString &)>(22, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 5 }, { QMetaType::QString, 6 },
        }}),
        // Signal 'userOffline'
        QtMocHelpers::SignalData<void(int, const QString &)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 5 }, { QMetaType::QString, 6 },
        }}),
        // Signal 'onlineUsersReceived'
        QtMocHelpers::SignalData<void(const QList<QPair<int,QString>> &)>(24, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 25, 26 },
        }}),
        // Signal 'historyReceived'
        QtMocHelpers::SignalData<void(int, const QJsonArray &)>(27, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 21 }, { QMetaType::QJsonArray, 28 },
        }}),
        // Signal 'forcedLogout'
        QtMocHelpers::SignalData<void(const QString &)>(29, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 30 },
        }}),
        // Slot 'readyRead'
        QtMocHelpers::SlotData<void()>(31, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onConnected'
        QtMocHelpers::SlotData<void()>(32, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onDisconnected'
        QtMocHelpers::SlotData<void()>(33, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Client, qt_meta_tag_ZN6ClientE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Client::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6ClientE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6ClientE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN6ClientE_t>.metaTypes,
    nullptr
} };

void Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Client *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disconnected(); break;
        case 2: _t->loginSuccess((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 3: _t->loginFailed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->registerSuccess(); break;
        case 5: _t->registerFailed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->usernameUpdated((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->usernameUpdateFailed(); break;
        case 8: _t->passwordUpdated(); break;
        case 9: _t->passwordUpdateFailed(); break;
        case 10: _t->newMessage((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[6]))); break;
        case 11: _t->userOnline((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 12: _t->userOffline((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 13: _t->onlineUsersReceived((*reinterpret_cast< std::add_pointer_t<QList<std::pair<int,QString>>>>(_a[1]))); break;
        case 14: _t->historyReceived((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QJsonArray>>(_a[2]))); break;
        case 15: _t->forcedLogout((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 16: _t->readyRead(); break;
        case 17: _t->onConnected(); break;
        case 18: _t->onDisconnected(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Client::*)()>(_a, &Client::connected, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)()>(_a, &Client::disconnected, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)(int , const QString & )>(_a, &Client::loginSuccess, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)(const QString & )>(_a, &Client::loginFailed, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)()>(_a, &Client::registerSuccess, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)(const QString & )>(_a, &Client::registerFailed, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)(const QString & )>(_a, &Client::usernameUpdated, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)()>(_a, &Client::usernameUpdateFailed, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)()>(_a, &Client::passwordUpdated, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)()>(_a, &Client::passwordUpdateFailed, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)(int , const QString & , const QString & , bool , const QString & , int )>(_a, &Client::newMessage, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)(int , const QString & )>(_a, &Client::userOnline, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)(int , const QString & )>(_a, &Client::userOffline, 12))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)(const QList<QPair<int,QString>> & )>(_a, &Client::onlineUsersReceived, 13))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)(int , const QJsonArray & )>(_a, &Client::historyReceived, 14))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)(const QString & )>(_a, &Client::forcedLogout, 15))
            return;
    }
}

const QMetaObject *Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6ClientE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void Client::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Client::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Client::loginSuccess(int _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2);
}

// SIGNAL 3
void Client::loginFailed(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void Client::registerSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Client::registerFailed(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void Client::usernameUpdated(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void Client::usernameUpdateFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void Client::passwordUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void Client::passwordUpdateFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void Client::newMessage(int _t1, const QString & _t2, const QString & _t3, bool _t4, const QString & _t5, int _t6)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 10, nullptr, _t1, _t2, _t3, _t4, _t5, _t6);
}

// SIGNAL 11
void Client::userOnline(int _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 11, nullptr, _t1, _t2);
}

// SIGNAL 12
void Client::userOffline(int _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 12, nullptr, _t1, _t2);
}

// SIGNAL 13
void Client::onlineUsersReceived(const QList<QPair<int,QString>> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 13, nullptr, _t1);
}

// SIGNAL 14
void Client::historyReceived(int _t1, const QJsonArray & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 14, nullptr, _t1, _t2);
}

// SIGNAL 15
void Client::forcedLogout(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 15, nullptr, _t1);
}
QT_WARNING_POP
