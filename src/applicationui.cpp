#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>
#include <bb/ImageData>
#include <bb/PixelFormat>

#include <bb/system/InvokeManager>
#include <bb/system/CardDoneMessage>

using namespace bb::cascades;
using namespace bb::system;


ApplicationUI::ApplicationUI(bb::cascades::Application *app) :
		QObject(app) {
	// prepare the localization
	m_pTranslator = new QTranslator(this);
	m_pLocaleHandler = new LocaleHandler(this);
	if (!QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()),
			this, SLOT(onSystemLanguageChanged()))) {
		// This is an abnormal situation! Something went wrong!
		// Add own code to recover here
		qWarning() << "Recovering from a failed connect()";
	}
	// initial load
	onSystemLanguageChanged();

	// Create scene document from main.qml asset, the parent is set
	// to ensure the document gets destroyed properly at shut down.
	QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
	qml->setContextProperty("_controller", this);
	// Create root object for the UI
	AbstractPane *root = qml->createRootObject<AbstractPane>();

	// Set created root object as the application scene
	app->setScene(root);
}

void ApplicationUI::onSystemLanguageChanged() {
	QCoreApplication::instance()->removeTranslator(m_pTranslator);
	// Initiate, load and install the application translation files.
	QString locale_string = QLocale().name();
	QString file_name = QString("ImageTest_%1").arg(locale_string);
	if (m_pTranslator->load(file_name, "app/native/qm")) {
		QCoreApplication::instance()->installTranslator(m_pTranslator);
	}
}

void ApplicationUI::closeCard() {
	InvokeManager im;
	CardDoneMessage message;
	im.sendCardDone(message);
}

void ApplicationUI::invoked(bb::system::InvokeRequest request) {
	qDebug() << "AQUIIIIIII" << request.target();
	m_imageSource = request.uri().toString();
	emit this->imageSourceChanged();
}

bb::ImageData fromQImage(const QImage &qImage) {
	bb::ImageData imageData(bb::PixelFormat::RGBA_Premultiplied, qImage.width(),
			qImage.height());
	unsigned char *dstLine = imageData.pixels();
	for (int y = 0; y < imageData.height(); y++) {
		unsigned char * dst = dstLine;
		for (int x = 0; x < imageData.width(); x++) {
			QRgb srcPixel = qImage.pixel(x, y);
			*dst++ = qRed(srcPixel);
			*dst++ = qGreen(srcPixel);
			*dst++ = qBlue(srcPixel);
			*dst++ = qAlpha(srcPixel);
		}
		dstLine += imageData.bytesPerLine();
	}
	return imageData;
}

bb::ImageData fromImageFile(const QString &path, float scale) {
	QImage tmp(path);
	QSize newSize(tmp.size().width() * scale, tmp.size().height() * scale);
	tmp = tmp.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	return fromQImage(tmp);
}

QVariantMap ApplicationUI::getImageMetadata(const QString & filePath) {
	QVariantMap ret;
	qDebug() << QDir::currentPath() + "/app/native/assets/" + filePath;
	QImage tmp(QDir::currentPath() + "/app/native/assets/" + filePath);
	ret["bytes"] = QVariant(tmp.byteCount());
	ret["width"] = QVariant(tmp.size().width());
	ret["height"] = QVariant(tmp.size().height());
	qDebug() << ret;
	return ret;
}
