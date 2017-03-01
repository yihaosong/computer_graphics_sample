/****************************************************************************
** Meta object code from reading C++ file 'HW4.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../hw4/HW4.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HW4.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HW4_t {
    QByteArrayData data[8];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HW4_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HW4_t qt_meta_stringdata_HW4 = {
    {
QT_MOC_LITERAL(0, 0, 3), // "HW4"
QT_MOC_LITERAL(1, 4, 13), // "changeDisplay"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 10), // "changeGeom"
QT_MOC_LITERAL(4, 30, 10), // "changeSize"
QT_MOC_LITERAL(5, 41, 11), // "changeSpeed"
QT_MOC_LITERAL(6, 53, 14), // "startAnimation"
QT_MOC_LITERAL(7, 68, 13) // "stopAnimation"

    },
    "HW4\0changeDisplay\0\0changeGeom\0changeSize\0"
    "changeSpeed\0startAnimation\0stopAnimation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HW4[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x0a /* Public */,
       3,    1,   47,    2, 0x0a /* Public */,
       4,    1,   50,    2, 0x0a /* Public */,
       5,    1,   53,    2, 0x0a /* Public */,
       6,    0,   56,    2, 0x0a /* Public */,
       7,    0,   57,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void HW4::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HW4 *_t = static_cast<HW4 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeDisplay((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->changeGeom((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->changeSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->changeSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->startAnimation(); break;
        case 5: _t->stopAnimation(); break;
        default: ;
        }
    }
}

const QMetaObject HW4::staticMetaObject = {
    { &HW::staticMetaObject, qt_meta_stringdata_HW4.data,
      qt_meta_data_HW4,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HW4::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HW4::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HW4.stringdata0))
        return static_cast<void*>(const_cast< HW4*>(this));
    return HW::qt_metacast(_clname);
}

int HW4::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = HW::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
