#pragma once

#include <QSettings>

class raii_settings_group {
public:
	raii_settings_group(const raii_settings_group &) = delete;
	raii_settings_group(raii_settings_group &&) = delete;
	raii_settings_group &operator = (const raii_settings_group &) = delete;
	raii_settings_group &operator = (raii_settings_group &&) = delete;

	raii_settings_group(QSettings &settings, const QString &key)
			: m_settings(settings) {
		m_settings.beginGroup(key);
	}

	raii_settings_group(QSettings &settings, const std::string &key)
			: raii_settings_group(settings, QString::fromStdString(key)) {}

	raii_settings_group(QSettings &settings, const char *key)
			: raii_settings_group(settings, QString::fromUtf8(key)) {}

	~raii_settings_group() {
		m_settings.endGroup();
	}

private:
	QSettings &m_settings;
};
