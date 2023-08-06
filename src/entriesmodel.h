/**
 * SPDX-FileCopyrightText: 2020 Tobias Fella <tobias.fella@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
 */

#pragma once

#include <QAbstractListModel>
#include <QHash>
#include <QObject>
#include <QString>

#include "feed.h"

struct Entry {
    QString feedUrl;
    QString id;
    QString title;
    QString content;
    QString authors;
    QDateTime created;
    QDateTime updated;
    QString link;
    bool read;
};

class EntriesModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QString feedUrl READ feedUrl WRITE setFeedUrl NOTIFY feedUrlChanged)

public:
    enum Roles {
        IdRole = Qt::DisplayRole,
        TitleRole,
        ContentRole,
        AuthorsRole,
        CreatedRole,
        UpdatedRole,
        LinkRole,
        BaseUrlRole,
        ReadRole,
    };
    Q_ENUM(Roles);
    explicit EntriesModel(QObject *parent = nullptr);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent) const override;

    QString feedUrl() const;
    void setFeedUrl(const QString &feedUrl);

Q_SIGNALS:
    void feedUrlChanged();

private:
    void loadEntry(int index) const;
    QString m_feedUrl;
    mutable QHash<int, Entry> m_entries;
};
