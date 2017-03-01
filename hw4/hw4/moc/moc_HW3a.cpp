/****************************************************************************
** Meta object code from reading C++ file 'HW3a.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../HW3a.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HW3a.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HW3a_t {
    QByteArrayData data[6];
    char stringdata0[54];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HW3a_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HW3a_t qt_meta_stringdata_HW3a = {
    {
QT_MOC_LITERAL(0, 0, 4), // "HW3a"
QT_MOC_LITERAL(1, 5, 11), // "changeTheta"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 12), // "changeSubdiv"
QT_MOC_LITERAL(4, 31, 11), // "changeTwist"
QT_MOC_LITERAL(5, 43, 10) // "changeWire"

    },
    "HW3a\0changeTheta\0\0changeSubdiv\0"
    "changeTwist\0changeWire"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HW3a[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       3,    1,   37,    2, 0x0a /* Public */,
       4,    1,   40,    2, 0x0a /* Public */,
       5,    1,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void HW3a::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HW3a *_t = static_cast<HW3a *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeTheta((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->changeSubdiv((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->changeTwist((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->changeWire((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject HW3a::staticMetaObject = {
    { &HW::staticMetaObject, qt_meta_stringdata_HW3a.data,
      qt_meta_data_HW3a,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HW3a::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HW3a::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HW3a.stringdata0))
        return static_cast<void*>(const_cast< HW3a*>(this));
    return HW::qt_metacast(_clname);
}

int HW3a::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = HW::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
