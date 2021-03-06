#ifndef RECOMMENT_H
#define RECOMMENT_H

#include <QObject>
#include <QList>

class CritiqueRecommender;
class Offer;
class AttributeFactory;
class Relationship;
class Offer;
class Token;
class ModifierToken;
class AttributeToken;

class Recomment : public QObject
{
    Q_OBJECT

signals:
    void recommend(const Offer* offer, const QString& description);
    void noMatchFor(const QString& critique);

public:
    explicit Recomment(QObject *parent = 0);
    ~Recomment();
    AttributeFactory* getAttributeFactory() const;

public slots:
    /// Initialize recomment
    bool init();
    /// Initialize recomment
    void reset();

    /// Parses the given voice command to one or more
    /// critiques
    /// Returns the interpretation (user presentable)
    QString critique(const QString& command);

private:
    CritiqueRecommender *m_recommender;
    AttributeFactory *m_attributeFactory;
    QList<Token*> m_acceptedTokens;
    const Offer *m_currentRecommendation;

    /// parses the database of offers from the given casebase XML file
    /// and returns the list of found offers; if an error occured,
    /// *okay will be set to false
    QList<Offer*> parseCasebase(const QString& path, const QString& imageBasePath, bool* okay) const;

    /// Reads the given nlp.xml to build the internal
    /// representation of the target language
    bool setupLanguage(const QString& path);

    Relationship* buildRelationship(const Offer *offer, const AttributeToken* attributeToken,
                                    const QString &attributeValue,
                                    const ModifierToken* modifierToken, double modifierFactor) const;


private slots:
    void recommendationChanged(const Offer *o, const QString &explanation);
    
};

#endif // RECOMMENT_H
