/*
 * Copyright (C) 2014-2016 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SYSTEMIMAGE_H
#define SYSTEMIMAGE_H

#include <QObject>
#include <QMap>

class SystemImage : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(SystemImage)

    Q_PROPERTY(bool updateAvailable READ updateAvailable NOTIFY updateAvailableStatus)
    Q_PROPERTY(bool updateDownloading READ updateDownloading NOTIFY updateAvailableStatus)
    Q_PROPERTY(QString availableVersion READ availableVersion NOTIFY updateAvailableStatus)
    Q_PROPERTY(QString updateSize READ updateSize NOTIFY updateAvailableStatus)

    Q_PROPERTY(bool updateDownloaded READ updateDownloaded NOTIFY updateDownloadedChanged)

public:
    explicit SystemImage(QObject *parent = nullptr);
    ~SystemImage() = default;

    bool updateAvailable() const { return m_updateAvailable; }
    bool updateDownloading() const { return m_downloading; }
    QString availableVersion() const { return m_availableVersion; }
    QString updateSize() const { return m_updateSize; }

    bool updateDownloaded() const { return m_downloaded; }

public Q_SLOTS:
    Q_INVOKABLE void checkForUpdate();
    Q_INVOKABLE void applyUpdate();
    Q_INVOKABLE void factoryReset();

private Q_SLOTS:
    void onUpdateAvailableStatus(bool is_available, bool updateDownloading, const QString &available_version,
                                 int update_size, const QString &last_update_date, const QString &error_reason);
    void onUpdateDownloaded(bool downloaded);
    void onUpdateFailed(int consecutive_failure_count, const QString & last_reason);
    void onUpdateApplied(bool applied);

Q_SIGNALS:
    void updateAvailableStatus();
    void updateDownloadedChanged();

private:
    void resetUpdateStatus();
    QString formatSize(quint64 size) const;

private:
    bool m_updateAvailable = false;
    bool m_downloading = false;
    bool m_downloaded = false;
    QString m_availableVersion;
    QString m_updateSize;
    QString m_lastUpdateDate;
    QString m_errorReason;
    bool m_updateDownloaded;
};

#endif // SYSTEMIMAGE_H
