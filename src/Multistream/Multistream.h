#include <vector>

namespace Tyleo
{
    namespace
    {
        class MultistreamEnd{};
    }

    template <typename TCurrent, typename ... TTail>
    class Multistream :
        private Multistream<TCurrent>, private Multistream<TTail ...>
    {
    public:
        Multistream(TCurrent & currentStream, TTail & ... tailStreams) :
            Multistream<TCurrent>::Multistream(currentStream),
            Multistream<TTail ...>::Multistream(tailStreams ...)
        {}

        template <typename TOutput>
        Multistream<TCurrent, TTail ...> & operator << (const TOutput & output)
        {
            Multistream<TCurrent>::operator<<(output);
            Multistream<TTail ...>::operator<<(output);
            return *this;
        }
    };

    template <typename TCurrent>
    class Multistream<TCurrent>
    {
    public:
        Multistream(TCurrent & currentStream) :
            _stream{ currentStream }
        {}

        template <typename TOutput>
        Multistream<TCurrent> & operator << (const TOutput & output)
        {
            _stream << output;
            return *this;
        }

    private:
        TCurrent & _stream;
    };

    template <>
    class Multistream<MultistreamEnd>
    {
    public:
        Multistream(MultistreamEnd & multistreamEnd)
        {}

        template <typename TOutput>
        Multistream<MultistreamEnd> & operator << (const TOutput & output)
        {
            return *this;
        }
    };

    template <typename TCurrent, typename ... TTail>
    Multistream<TCurrent, TTail ..., MultistreamEnd> MakeMultistream(TCurrent & currentStream, TTail & ... tailStreams)
    {
        return Multistream<TCurrent, TTail ..., MultistreamEnd>{ currentStream, tailStreams ..., MultistreamEnd{} };
    }
}
