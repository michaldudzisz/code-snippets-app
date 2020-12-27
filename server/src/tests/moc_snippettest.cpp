/****************************************************************************
** Meta object code from reading C++ file 'snippettest.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "snippettest.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'snippettest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SnippetTest_t {
    QByteArrayData data[22];
    char stringdata0[254];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SnippetTest_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SnippetTest_t qt_meta_stringdata_SnippetTest = {
    {
QT_MOC_LITERAL(0, 0, 11), // "SnippetTest"
QT_MOC_LITERAL(1, 12, 11), // "constructor"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 18), // "copyingConstructor"
QT_MOC_LITERAL(4, 44, 17), // "noDateConstructor"
QT_MOC_LITERAL(5, 62, 21), // "allMembersConstructor"
QT_MOC_LITERAL(6, 84, 18), // "assignmentOperator"
QT_MOC_LITERAL(7, 103, 6), // "toJson"
QT_MOC_LITERAL(8, 110, 8), // "fromJson"
QT_MOC_LITERAL(9, 119, 17), // "fromJsonRValueArg"
QT_MOC_LITERAL(10, 137, 9), // "setAuthor"
QT_MOC_LITERAL(11, 147, 8), // "setTitle"
QT_MOC_LITERAL(12, 156, 10), // "setCreated"
QT_MOC_LITERAL(13, 167, 7), // "setLang"
QT_MOC_LITERAL(14, 175, 10), // "setContent"
QT_MOC_LITERAL(15, 186, 6), // "author"
QT_MOC_LITERAL(16, 193, 5), // "title"
QT_MOC_LITERAL(17, 199, 7), // "created"
QT_MOC_LITERAL(18, 207, 4), // "lang"
QT_MOC_LITERAL(19, 212, 7), // "content"
QT_MOC_LITERAL(20, 220, 13), // "fieldToString"
QT_MOC_LITERAL(21, 234, 19) // "fieldToItsMaxLength"

    },
    "SnippetTest\0constructor\0\0copyingConstructor\0"
    "noDateConstructor\0allMembersConstructor\0"
    "assignmentOperator\0toJson\0fromJson\0"
    "fromJsonRValueArg\0setAuthor\0setTitle\0"
    "setCreated\0setLang\0setContent\0author\0"
    "title\0created\0lang\0content\0fieldToString\0"
    "fieldToItsMaxLength"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SnippetTest[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x08 /* Private */,
       3,    0,  115,    2, 0x08 /* Private */,
       4,    0,  116,    2, 0x08 /* Private */,
       5,    0,  117,    2, 0x08 /* Private */,
       6,    0,  118,    2, 0x08 /* Private */,
       7,    0,  119,    2, 0x08 /* Private */,
       8,    0,  120,    2, 0x08 /* Private */,
       9,    0,  121,    2, 0x08 /* Private */,
      10,    0,  122,    2, 0x08 /* Private */,
      11,    0,  123,    2, 0x08 /* Private */,
      12,    0,  124,    2, 0x08 /* Private */,
      13,    0,  125,    2, 0x08 /* Private */,
      14,    0,  126,    2, 0x08 /* Private */,
      15,    0,  127,    2, 0x08 /* Private */,
      16,    0,  128,    2, 0x08 /* Private */,
      17,    0,  129,    2, 0x08 /* Private */,
      18,    0,  130,    2, 0x08 /* Private */,
      19,    0,  131,    2, 0x08 /* Private */,
      20,    0,  132,    2, 0x08 /* Private */,
      21,    0,  133,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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

void SnippetTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SnippetTest *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->constructor(); break;
        case 1: _t->copyingConstructor(); break;
        case 2: _t->noDateConstructor(); break;
        case 3: _t->allMembersConstructor(); break;
        case 4: _t->assignmentOperator(); break;
        case 5: _t->toJson(); break;
        case 6: _t->fromJson(); break;
        case 7: _t->fromJsonRValueArg(); break;
        case 8: _t->setAuthor(); break;
        case 9: _t->setTitle(); break;
        case 10: _t->setCreated(); break;
        case 11: _t->setLang(); break;
        case 12: _t->setContent(); break;
        case 13: _t->author(); break;
        case 14: _t->title(); break;
        case 15: _t->created(); break;
        case 16: _t->lang(); break;
        case 17: _t->content(); break;
        case 18: _t->fieldToString(); break;
        case 19: _t->fieldToItsMaxLength(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject SnippetTest::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_SnippetTest.data,
    qt_meta_data_SnippetTest,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SnippetTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SnippetTest::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SnippetTest.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SnippetTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
