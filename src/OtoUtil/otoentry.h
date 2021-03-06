#ifndef OTOENTRY_H
#define OTOENTRY_H

#include "../QKiraUTAUUtils_global.h"
#include <QObject>
#include <QFile>
#include <QTextCodec>

constexpr int OTOENTRY_DEFAULT_PRECISION = 3;

/// OtoEntry 定义了一条原音设定条目。
class QKIRAUTAUUTILS_EXPORT OtoEntry : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged);
    Q_PROPERTY(QString alias READ alias WRITE setAlias NOTIFY aliasChanged);
    Q_PROPERTY(double left READ left WRITE setLeft NOTIFY leftChanged);
    Q_PROPERTY(double consonant READ consonant WRITE setConsonant NOTIFY consonantChanged);
    Q_PROPERTY(double right READ right WRITE setRight NOTIFY rightChanged);
    Q_PROPERTY(double preUtterance READ preUtterance WRITE setPreUtterance NOTIFY preUtteranceChanged);
    Q_PROPERTY(double overlap READ overlap WRITE setOverlap NOTIFY overlapChanged);

public:
    OtoEntry(QString m_fileName,
             QString m_alias,
             double m_left,
             double m_consonant,
             double m_right,
             double m_preUtterance,
             double m_overlap,
             QObject *parent = nullptr);
    explicit OtoEntry(const QString& otoString);
    OtoEntry(const OtoEntry& other);

    OtoEntry& operator=(const OtoEntry& rhs);

    enum OtoEntryError{
        UnknownError,
        FileNameSeparatorNotFound,
        LeftConvertFailed,
        ConsonantConvertFailed,
        RightConvertFailed,
        PreUtteranceConvertFailed,
        OverlapConvertFailed,
        EmptyOtoString,
        EmptyFileName,
    };
    Q_ENUM(OtoEntryError);

    enum OtoParameter{
        FileName = 0x1,
        Alias = 0x2,
        Left = 0x4,
        Consonant = 0x8,
        Right = 0x10,
        PreUtterance = 0x20,
        Overlap = 0x40,
    };

    Q_DECLARE_FLAGS(OtoParameters, OtoParameter);
    Q_FLAG(OtoParameter);


    enum OtoParameterOrder{
        FILENAME, ALIAS, LEFT, CONSONANT, RIGHT, PREUTTERANCE, OVERLAP
    };
    Q_ENUM(OtoParameterOrder);

    static const int OtoParameterCount;

    /*!
    @brief 该条条目的文件名属性。
    fileName 告知UTAU引擎时应该在哪个文件中寻找对应原音块。
    这个文件名相对于oto.ini所在的文件夹。
    @see void setFileName(const QString& value)
    */
    QString fileName() const;

    /*!
    @brief 设置该条条目的文件名属性。
    @see QString fileName() const
    */
    void setFileName(const QString& value);

    QString alias() const;
    void setAlias(const QString& value);

    double left() const;
    void setLeft(double value);

    double consonant() const;
    void setConsonant(double value);

    double right() const;
    void setRight(double value);

    double preUtterance() const;
    void setPreUtterance(double value);

    double overlap() const;
    void setOverlap(double value);

    QVariant getParameter(OtoParameter parameter) const;
    QVariant getParameter(OtoParameterOrder parameter) const;

    void setParameter(OtoParameter parameter, QVariant value);
    void setParameter(OtoParameterOrder parameter, QVariant value);

    static OtoParameter getParameterFlag(OtoParameterOrder order);
    static OtoParameterOrder getParameterOrder(OtoParameter flag);

    OtoEntryError error() const;
    QString errorString() const;

    QString toString(int precision = OTOENTRY_DEFAULT_PRECISION) const;

    Q_INVOKABLE bool isValid() const{
        return m_valid;
    }

    bool operator==(const OtoEntry& rhs) const;
    bool operator!=(const OtoEntry& rhs) const;

signals:
    void fileNameChanged();
    void aliasChanged();
    void leftChanged();
    void consonantChanged();
    void rightChanged();
    void preUtteranceChanged();
    void overlapChanged();

private:
    QString m_fileName {};
    QString m_alias {};
    double m_left {};
    double m_consonant {};
    double m_right {};
    double m_preUtterance {};
    double m_overlap {};

    OtoEntryError m_error{UnknownError};
    void setError(OtoEntryError error);
    bool m_valid = false;

    void setValid(bool valid);
};
Q_DECLARE_OPERATORS_FOR_FLAGS(OtoEntry::OtoParameters);

using OtoEntryList = QList<OtoEntry>;

namespace OtoEntryFunctions {
    Q_NAMESPACE_EXPORT(QKIRAUTAUUTILS_EXPORT)
    enum CharacterCase{
        Upper, Lower
    };
    Q_ENUM_NS(CharacterCase)

    QKIRAUTAUUTILS_EXPORT QStringList getPitchStringRange(const QString& bottomPitch, const QString& topPitch, CharacterCase characterCase = Upper);
    QKIRAUTAUUTILS_EXPORT QString removePitchSuffix(QString alias, const QString& bottomPitch, const QString& topPitch, Qt::CaseSensitivity cs = Qt::CaseInsensitive, CharacterCase pitchRangeCharacterCase = CharacterCase::Upper, QString* pitchRemoved = nullptr);
    QKIRAUTAUUTILS_EXPORT QString removePitchPrefix(QString alias, const QString& bottomPitch, const QString& topPitch, Qt::CaseSensitivity cs = Qt::CaseInsensitive, CharacterCase pitchRangeCharacterCase = CharacterCase::Upper, QString* pitchRemoved = nullptr);
    QKIRAUTAUUTILS_EXPORT QString removeSuffix(QString string, const QString& suffix, Qt::CaseSensitivity cs = Qt::CaseSensitive, bool* removed = nullptr);
    QKIRAUTAUUTILS_EXPORT QString removePrefix(QString string, const QString& prefix, Qt::CaseSensitivity cs = Qt::CaseSensitive, bool* removed = nullptr);
    QKIRAUTAUUTILS_EXPORT QString getDigitSuffix(const QString& string, int* position = nullptr);
    ///@deprecated
    QKIRAUTAUUTILS_EXPORT int  writeOtoListToFile [[deprecated]] (QFile& file, const OtoEntryList& entryList, QTextCodec* textCodec = QTextCodec::codecForName("Shift-JIS"));

    QKIRAUTAUUTILS_EXPORT bool writeOtoListToFile(const QString& fileName, const OtoEntryList& entryList, int precision = OTOENTRY_DEFAULT_PRECISION, QFileDevice::FileError* error = nullptr, QString* errorString = nullptr , QTextCodec* textCodec = QTextCodec::codecForName("Shift-JIS"),
                                                  bool directWriteFallback = true);
}


#endif // OTOENTRY_H
