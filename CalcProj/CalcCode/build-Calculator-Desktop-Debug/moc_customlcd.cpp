/****************************************************************************
** Meta object code from reading C++ file 'customlcd.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Calculator/customlcd.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'customlcd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CustomLCD_t {
    QByteArrayData data[12];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CustomLCD_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CustomLCD_t qt_meta_stringdata_CustomLCD = {
    {
QT_MOC_LITERAL(0, 0, 9), // "CustomLCD"
QT_MOC_LITERAL(1, 10, 16), // "changeFirstValue"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 20), // "actualizaPrimerValor"
QT_MOC_LITERAL(4, 49, 5), // "valor"
QT_MOC_LITERAL(5, 55, 21), // "actualizaSegundoValor"
QT_MOC_LITERAL(6, 77, 4), // "suma"
QT_MOC_LITERAL(7, 82, 5), // "resta"
QT_MOC_LITERAL(8, 88, 10), // "multiplica"
QT_MOC_LITERAL(9, 99, 6), // "divide"
QT_MOC_LITERAL(10, 106, 16), // "changeAccumulate"
QT_MOC_LITERAL(11, 123, 9) // "changeAbs"

    },
    "CustomLCD\0changeFirstValue\0\0"
    "actualizaPrimerValor\0valor\0"
    "actualizaSegundoValor\0suma\0resta\0"
    "multiplica\0divide\0changeAccumulate\0"
    "changeAbs"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CustomLCD[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   62,    2, 0x0a /* Public */,
       5,    1,   65,    2, 0x0a /* Public */,
       6,    0,   68,    2, 0x0a /* Public */,
       7,    0,   69,    2, 0x0a /* Public */,
       8,    0,   70,    2, 0x0a /* Public */,
       9,    0,   71,    2, 0x0a /* Public */,
      10,    0,   72,    2, 0x0a /* Public */,
      11,    0,   73,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    4,
    QMetaType::Void, QMetaType::Double,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CustomLCD::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CustomLCD *_t = static_cast<CustomLCD *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeFirstValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->actualizaPrimerValor((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->actualizaSegundoValor((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->suma(); break;
        case 4: _t->resta(); break;
        case 5: _t->multiplica(); break;
        case 6: _t->divide(); break;
        case 7: _t->changeAccumulate(); break;
        case 8: _t->changeAbs(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (CustomLCD::*_t)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CustomLCD::changeFirstValue)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject CustomLCD::staticMetaObject = {
    { &QLCDNumber::staticMetaObject, qt_meta_stringdata_CustomLCD.data,
      qt_meta_data_CustomLCD,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CustomLCD::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomLCD::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CustomLCD.stringdata0))
        return static_cast<void*>(this);
    return QLCDNumber::qt_metacast(_clname);
}

int CustomLCD::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLCDNumber::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void CustomLCD::changeFirstValue(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
