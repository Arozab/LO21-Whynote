/****************************************************************************
** Meta object code from reading C++ file 'fenetrecorbeille.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../fenetrecorbeille.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fenetrecorbeille.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FenetreCorbeille_t {
    QByteArrayData data[7];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FenetreCorbeille_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FenetreCorbeille_t qt_meta_stringdata_FenetreCorbeille = {
    {
QT_MOC_LITERAL(0, 0, 16), // "FenetreCorbeille"
QT_MOC_LITERAL(1, 17, 13), // "activerBouton"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 13), // "restaurerNote"
QT_MOC_LITERAL(4, 46, 6), // "Notes*"
QT_MOC_LITERAL(5, 53, 13), // "supprimerNote"
QT_MOC_LITERAL(6, 67, 14) // "viderCorbeille"

    },
    "FenetreCorbeille\0activerBouton\0\0"
    "restaurerNote\0Notes*\0supprimerNote\0"
    "viderCorbeille"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FenetreCorbeille[] = {

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
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       5,    0,   36,    2, 0x0a /* Public */,
       6,    0,   37,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    0x80000000 | 4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FenetreCorbeille::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FenetreCorbeille *_t = static_cast<FenetreCorbeille *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->activerBouton(); break;
        case 1: { Notes* _r = _t->restaurerNote();
            if (_a[0]) *reinterpret_cast< Notes**>(_a[0]) = _r; }  break;
        case 2: _t->supprimerNote(); break;
        case 3: _t->viderCorbeille(); break;
        default: ;
        }
    }
}

const QMetaObject FenetreCorbeille::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FenetreCorbeille.data,
      qt_meta_data_FenetreCorbeille,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FenetreCorbeille::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FenetreCorbeille::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FenetreCorbeille.stringdata0))
        return static_cast<void*>(const_cast< FenetreCorbeille*>(this));
    return QWidget::qt_metacast(_clname);
}

int FenetreCorbeille::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
