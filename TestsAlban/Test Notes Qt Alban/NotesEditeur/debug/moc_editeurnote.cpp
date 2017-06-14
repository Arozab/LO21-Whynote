/****************************************************************************
** Meta object code from reading C++ file 'editeurnote.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../editeurnote.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editeurnote.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EditeurNote_t {
    QByteArrayData data[10];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EditeurNote_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EditeurNote_t qt_meta_stringdata_EditeurNote = {
    {
QT_MOC_LITERAL(0, 0, 11), // "EditeurNote"
QT_MOC_LITERAL(1, 12, 13), // "activerEditer"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 13), // "annuleEdition"
QT_MOC_LITERAL(4, 41, 8), // "supprime"
QT_MOC_LITERAL(5, 50, 12), // "supprimeNote"
QT_MOC_LITERAL(6, 63, 12), // "restaureNote"
QT_MOC_LITERAL(7, 76, 10), // "sauverNote"
QT_MOC_LITERAL(8, 87, 8), // "restaure"
QT_MOC_LITERAL(9, 96, 13) // "activerSauver"

    },
    "EditeurNote\0activerEditer\0\0annuleEdition\0"
    "supprime\0supprimeNote\0restaureNote\0"
    "sauverNote\0restaure\0activerSauver"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditeurNote[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void EditeurNote::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EditeurNote *_t = static_cast<EditeurNote *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->activerEditer(); break;
        case 1: _t->annuleEdition(); break;
        case 2: _t->supprime(); break;
        case 3: _t->supprimeNote(); break;
        case 4: _t->restaureNote(); break;
        case 5: _t->sauverNote(); break;
        case 6: _t->restaure(); break;
        case 7: _t->activerSauver(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject EditeurNote::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EditeurNote.data,
      qt_meta_data_EditeurNote,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EditeurNote::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditeurNote::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EditeurNote.stringdata0))
        return static_cast<void*>(const_cast< EditeurNote*>(this));
    return QWidget::qt_metacast(_clname);
}

int EditeurNote::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
struct qt_meta_stringdata_ArticleEditeur_t {
    QByteArrayData data[5];
    char stringdata0[55];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ArticleEditeur_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ArticleEditeur_t qt_meta_stringdata_ArticleEditeur = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ArticleEditeur"
QT_MOC_LITERAL(1, 15, 10), // "sauverNote"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 13), // "activerEditer"
QT_MOC_LITERAL(4, 41, 13) // "annuleEdition"

    },
    "ArticleEditeur\0sauverNote\0\0activerEditer\0"
    "annuleEdition"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ArticleEditeur[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ArticleEditeur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ArticleEditeur *_t = static_cast<ArticleEditeur *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sauverNote(); break;
        case 1: _t->activerEditer(); break;
        case 2: _t->annuleEdition(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ArticleEditeur::staticMetaObject = {
    { &EditeurNote::staticMetaObject, qt_meta_stringdata_ArticleEditeur.data,
      qt_meta_data_ArticleEditeur,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ArticleEditeur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ArticleEditeur::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ArticleEditeur.stringdata0))
        return static_cast<void*>(const_cast< ArticleEditeur*>(this));
    return EditeurNote::qt_metacast(_clname);
}

int ArticleEditeur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = EditeurNote::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
struct qt_meta_stringdata_TacheEditeur_t {
    QByteArrayData data[5];
    char stringdata0[53];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TacheEditeur_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TacheEditeur_t qt_meta_stringdata_TacheEditeur = {
    {
QT_MOC_LITERAL(0, 0, 12), // "TacheEditeur"
QT_MOC_LITERAL(1, 13, 10), // "sauverNote"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 13), // "activerEditer"
QT_MOC_LITERAL(4, 39, 13) // "annuleEdition"

    },
    "TacheEditeur\0sauverNote\0\0activerEditer\0"
    "annuleEdition"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TacheEditeur[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TacheEditeur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TacheEditeur *_t = static_cast<TacheEditeur *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sauverNote(); break;
        case 1: _t->activerEditer(); break;
        case 2: _t->annuleEdition(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject TacheEditeur::staticMetaObject = {
    { &EditeurNote::staticMetaObject, qt_meta_stringdata_TacheEditeur.data,
      qt_meta_data_TacheEditeur,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TacheEditeur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TacheEditeur::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TacheEditeur.stringdata0))
        return static_cast<void*>(const_cast< TacheEditeur*>(this));
    return EditeurNote::qt_metacast(_clname);
}

int TacheEditeur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = EditeurNote::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
struct qt_meta_stringdata_NoteFichierEditeur_t {
    QByteArrayData data[5];
    char stringdata0[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NoteFichierEditeur_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NoteFichierEditeur_t qt_meta_stringdata_NoteFichierEditeur = {
    {
QT_MOC_LITERAL(0, 0, 18), // "NoteFichierEditeur"
QT_MOC_LITERAL(1, 19, 10), // "sauverNote"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 13), // "activerEditer"
QT_MOC_LITERAL(4, 45, 13) // "annuleEdition"

    },
    "NoteFichierEditeur\0sauverNote\0\0"
    "activerEditer\0annuleEdition"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NoteFichierEditeur[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void NoteFichierEditeur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NoteFichierEditeur *_t = static_cast<NoteFichierEditeur *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sauverNote(); break;
        case 1: _t->activerEditer(); break;
        case 2: _t->annuleEdition(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject NoteFichierEditeur::staticMetaObject = {
    { &EditeurNote::staticMetaObject, qt_meta_stringdata_NoteFichierEditeur.data,
      qt_meta_data_NoteFichierEditeur,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NoteFichierEditeur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NoteFichierEditeur::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NoteFichierEditeur.stringdata0))
        return static_cast<void*>(const_cast< NoteFichierEditeur*>(this));
    return EditeurNote::qt_metacast(_clname);
}

int NoteFichierEditeur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = EditeurNote::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
