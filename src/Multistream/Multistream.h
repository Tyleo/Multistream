#include <vector>

namespace Tyleo
{
    template <typename TCurrent, typename ... TTail>
    class Multistream :
        private Multistream<TTail ...>
    {
    public:
        Multistream(TCurrent & currentStream, TTail & ... tailStreams) :
            _stream{ currentStream },
            Multistream<TTail ...>::Multistream(tailStreams ...)
        {}

        template <typename TOutput>
        Multistream<TCurrent, TTail ...> & operator << (const TOutput & output)
        {
            _stream << output;
            Multistream<TTail ...>::operator<<(output);
            return *this;
        }

    private:
        TCurrent & _stream;
    };

    template <typename TCurrent>
    class Multistream<TCurrent>
    {
    public:
        Multistream(TCurrent & currentStream) :
            _stream{ currentStream }
        {}

        template <typename TOutput>
        Multistream<TCurrent> & operator << (TOutput & output)
        {
            _stream << output;
            return *this;
        }

    private:
        TCurrent & _stream;
    };

    template <typename TCurrent, typename ... TTail>
    Multistream<TCurrent, TTail ...> MakeMultistream(TCurrent & currentStream, TTail & ... tailStreams)
    {
        return Multistream<TCurrent, TTail ...>{currentStream, tailStreams ...};
    }
}
