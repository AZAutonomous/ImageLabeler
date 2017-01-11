#ifndef WRAPPINGQDIRITERATOR_H
#define WRAPPINGQDIRITERATOR_H

#include <QDirIterator>
#include <QDir>
#include <QFileInfo>
#include <QDirIterator>

class WrappingQDirIterator
{
public:
	WrappingQDirIterator(const QDir &dir, QDirIterator::IteratorFlags flags = QDirIterator::NoIteratorFlags);
	WrappingQDirIterator(const QString &path, QDirIterator::IteratorFlags flags = QDirIterator::NoIteratorFlags);
	WrappingQDirIterator(const QString &path, QDir::Filters filters, QDirIterator::IteratorFlags flags = QDirIterator::NoIteratorFlags);
	WrappingQDirIterator(const QString &path, const QStringList &nameFilters, QDir::Filters filters = QDir::NoFilter, QDirIterator::IteratorFlags flags = QDirIterator::NoIteratorFlags);
	virtual	~WrappingQDirIterator();
	QFileInfo	fileInfo() const;
	QString	fileName() const;
	QString	filePath() const;
	bool	hasNext();
	QString	next();
	QString	path() const;
private:
	void reloadIterator();

	QDirIterator *dirIterator;

	QDir *dir;
	QString *rootpath;
	QDir::Filters *filters;
	QStringList *nameFilters;
	QDirIterator::IteratorFlags *flags;

};

#endif // WRAPPINGQDIRITERATOR_H
