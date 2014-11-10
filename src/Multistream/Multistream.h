#include <vector>

namespace Tyleo
{
    template <typename ... TArgs>
    class Multistream;

    template <>
    class Multistream<>
    {
    public:
        Multistream() = default;

        template <typename TOutput>
        Multistream & operator << (const TOutput & output)
        {
            return *this;
        }

        Multistream & operator << (std::ostream & (* manip)(std::ostream &))
        {
            return *this;
        }
    };

    template <typename TCurrent,
              typename ... TTail>
    class Multistream<TCurrent, TTail ...> : private Multistream<TCurrent>,
                                             private Multistream<TTail ...>
    {
    public:
        Multistream() = default;

        Multistream(TCurrent & currentStream,
                    TTail & ... tailStreams) : Multistream<TCurrent>::Multistream(currentStream),
                                               Multistream<TTail ...>::Multistream(tailStreams ...)
        { }

        template <typename TOutput>
        Multistream<TCurrent,
                    TTail ...> & operator << (const TOutput & output)
        {
            Multistream<TCurrent>::operator<<(output);
            Multistream<TTail ...>::operator<<(output);

            return *this;
        }

        Multistream<TCurrent,
                    TTail ...> & operator << (std::ostream & (* manip)(std::ostream &))
        {
            Multistream<TCurrent>::operator<<(manip);
            Multistream<TTail ...>::operator<<(manip);

            return *this;
        }
    };

    template <typename TCurrent>
    class Multistream<TCurrent>
    {
    private:
        TCurrent * _stream;

    public:
        Multistream() = default;

        Multistream(TCurrent & currentStream) : _stream{ &currentStream }
        { }

        template <typename TOutput>
        Multistream<TCurrent> & operator << (const TOutput & output)
        {
            *_stream << output;

            return *this;
        }

        Multistream<TCurrent> & operator << (std::ostream & (* manip)(std::ostream &))
        {
            *_stream << (manip);

            return *this;
        }
    };

    template <typename TCurrent, typename ... TTail>
    Multistream<TCurrent, TTail ...> MakeMultistream(TCurrent & currentStream, TTail & ... tailStreams)
    {
        return Multistream<TCurrent, TTail ...>{ currentStream, tailStreams ... };
    }
}
