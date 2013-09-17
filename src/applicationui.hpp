#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QObject>
#include <QVariantMap>
#include <bb/system/InvokeManager>
namespace bb
{
    namespace cascades
    {
        class Application;
        class LocaleHandler;
    }
}

class QTranslator;

/*!
 * @brief Application object
 *
 *
 */

class ApplicationUI : public QObject
{
    Q_OBJECT
	Q_PROPERTY(QString imageSource READ imageSource NOTIFY imageSourceChanged)
public:
    ApplicationUI(bb::cascades::Application *app);
    virtual ~ApplicationUI() { }
    QString imageSource() {
    	return m_imageSource;
    }
    Q_INVOKABLE void closeCard();
    Q_INVOKABLE QVariantMap getImageMetadata(const QString & filePath);
private slots:
    void onSystemLanguageChanged();
    void invoked(bb::system::InvokeRequest);
Q_SIGNALS:
	void imageSourceChanged();
private:
    QTranslator* m_pTranslator;
    bb::cascades::LocaleHandler* m_pLocaleHandler;
    QString m_imageSource;
};

#endif /* ApplicationUI_HPP_ */
