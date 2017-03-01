/****************************************************************************
** Meta object code from reading C++ file 'HW1b.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../HW1b.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HW1b.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HW1b_t {
    QByteArrayData data[7];
    char stringdata0[42];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HW1b_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HW1b_t qt_meta_stringdata_HW1b = {
    {
QT_MOC_LITERAL(0, 0, 4), // "HW1b"
QT_MOC_LITERAL(1, 5, 5), // "flipY"
QT_MOC_LITERAL(2, 11, 0), // ""
QT_MOC_LITERAL(3, 12, 5), // "twist"
QT_MOC_LITERAL(4, 18, 6), // "aspect"
QT_MOC_LITERAL(5, 25, 6), // "rotate"
QT_MOC_LITERAL(6, 32, 9) // "subdivide"

    },
    "HW1b\0flipY\0\0twist\0aspect\0rotate\0"
    "subdivide"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HW1b[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       3,    0,   42,    2, 0x0a /* Public */,
       4,    1,   43,    2, 0x0a /* Public */,
       5,    1,   46,    2, 0x0a /* Public */,
       6,    1,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void HW1b::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HW1b *_t = static_cast<HW1b *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->flipY((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->twist(); break;
        case 2: _t->aspect((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->rotate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->subdivide((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject HW1b::staticMetaObject = {
    { &HW::staticMetaObject, qt_meta_stringdata_HW1b.data,
      qt_meta_data_HW1b,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HW1b::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HW1b::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HW1b.stringdata0))
        return static_cast<void*>(const_cast< HW1b*>(this));
    return HW::qt_metacast(_clname);
}

int HW1b::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = HW::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
