#include "wrappingqdiriterator.h"

WrappingQDirIterator::WrappingQDirIterator(const QDir &dir, QDirIterator::IteratorFlags flags) :
	dirIterator(new QDirIterator(dir, flags)),
	dir(new QDir(dir)),
	rootpath(nullptr),
	filters(nullptr),
	nameFilters(nullptr),
	flags(new QDirIterator::IteratorFlags(flags))
{

}

WrappingQDirIterator::WrappingQDirIterator(const QString &path, QDirIterator::IteratorFlags flags) :
	dirIterator(new QDirIterator(path, flags)),
	dir(nullptr),
	rootpath(new QString(path)),
	filters(nullptr),
	nameFilters(nullptr),
	flags(new QDirIterator::IteratorFlags(flags))
{

}

WrappingQDirIterator::WrappingQDirIterator(const QString &path, QDir::Filters filters, QDirIterator::IteratorFlags flags) :
	dirIterator(new QDirIterator(path, filters, flags)),
	dir(nullptr),
	rootpath(new QString(path)),
	filters(new QDir::Filters(filters)),
	nameFilters(nullptr),
	flags(new QDirIterator::IteratorFlags(flags))
{

}

WrappingQDirIterator::WrappingQDirIterator(const QString &path, const QStringList &nameFilters, QDir::Filters filters, QDirIterator::IteratorFlags flags) :
	dirIterator(new QDirIterator(path, nameFilters, filters, flags)),
	dir(nullptr),
	rootpath(new QString(path)),
	filters(new QDir::Filters(filters)),
	nameFilters(new QStringList(nameFilters)),
	flags(new QDirIterator::IteratorFlags(flags))
{

}

WrappingQDirIterator::~WrappingQDirIterator()
{
	delete dirIterator;
	delete dir;
	delete rootpath;
	delete filters;
	delete nameFilters;
	delete flags;
}

QFileInfo WrappingQDirIterator::fileInfo() const
{
	return dirIterator->fileInfo();
}

QString	WrappingQDirIterator::fileName() const
{
	return dirIterator->fileName();
}

QString	WrappingQDirIterator::filePath() const
{
	return dirIterator->filePath();
}

bool WrappingQDirIterator::hasNext()
{
	// Regular behavior
	if (dirIterator->hasNext()) {
		return true;
	}

	// "Wraparound" behavior - restart iterator from beginning
	else {
		// Reinitialize iterator to wrap around
		reloadIterator();

		return dirIterator->hasNext();
	}
}

QString	WrappingQDirIterator::next()
{
	// Skip past no longer existing files (error catching)
	while (dirIterator->hasNext()) {
		QString filepath = dirIterator->next();
		if (QDir().exists(filepath)) {
			return filepath;
		}
	}

	// No more elements
	return QString("");
}

QString	WrappingQDirIterator::path() const
{
	return dirIterator->path();
}

void WrappingQDirIterator::reloadIterator()
{
	// Delete old iterator
	delete dirIterator;

	// Instantiate new iterator
	if (dir != nullptr) {
		dirIterator = new QDirIterator(*dir, *flags);
	}
	else if (nameFilters != nullptr) {
		dirIterator = new QDirIterator(*rootpath, *nameFilters, *filters, *flags);
	}
	else if (filters != nullptr) {
		dirIterator = new QDirIterator(*rootpath, *filters, *flags);
	}
	else {
		dirIterator = new QDirIterator(*rootpath, *flags);
	}
}
