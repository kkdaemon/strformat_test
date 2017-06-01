#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

#include <benchmark/benchmark.h>

#include <fmt/format.h>
#include <fmt/printf.h>

#include <boost/format.hpp>

#include <tinyformat/tinyformat.h>

#if !defined(DISABLE_FASTFORMAT)
#   define FASTFORMAT_NO_VERSION_NAG
#   include <fastformat/fastformat.hpp>
#   include <fastformat/shims/conversion/filter_type/reals.hpp>
#endif

using std::cout;
using std::endl;

int i = 33;
long long ll = 1024ll * 1024ll * 1024ll * 1024ll * 34ll;
double d = -3.564556;
const char s[] = "this is a test";

static void test_snprintf(benchmark::State& state)
{
    while (state.KeepRunning())
    {
#if defined(_MSC_VER)
        int n = _scprintf("%d %X %lld %llX %f %e %s", i, i, ll, ll, d, d, s);
        std::string r(n + 1, 0);
        _snprintf_s(&r[0], n + 1, _TRUNCATE, "%d %X %lld %llX %f %e %s", i, i, ll, ll, d, d, s);
#else
        int n = snprintf(nullptr, 0, "%d %X %lld %llX %f %e %s", i, i, ll, ll, d, d, s);
        std::string r(n + 1, 0);
        snprintf(&r[0], n + 1, "%d %X %lld %llX %f %e %s", i, i, ll, ll, d, d, s);
#endif
        r.pop_back();
        benchmark::DoNotOptimize(r.c_str());
    }
}

static void test_snprintf_stackbuf(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        char buf[512];
#if defined(_MSC_VER)
        _snprintf_s(buf, _TRUNCATE, "%d %X %lld %llX %f %e %s", i, i, ll, ll, d, d, s);
#else
        snprintf(buf, sizeof(buf), "%d %X %lld %llX %f %e %s", i, i, ll, ll, d, d, s);
#endif
        benchmark::DoNotOptimize(buf);
    }
}

static void test_sstream(benchmark::State& state)
{
    using namespace std;

    while (state.KeepRunning())
    {
        stringstream ss;
        ss << i << " " << hex << i << dec << " " << ll << " " << hex << ll << dec << " " << d << " " << scientific << d << " " << s;
        std::string r = ss.str();
        benchmark::DoNotOptimize(r.c_str());
    }
}

static void test_fmt(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        std::string r = fmt::sprintf("%d %X %lld %llX %f %e %s", i, i, ll, ll, d, d, s);
        benchmark::DoNotOptimize(r.c_str());
    }
}

static void test_boost_format(benchmark::State& state)
{
    using namespace boost;
    while (state.KeepRunning())
    {
        std::string r = (format("%d %X %lld %llX %f %e %s") % i % i % ll % ll % d % d % s).str();
        benchmark::DoNotOptimize(r.c_str());
    }
}

#if !defined(DISABLE_FASTFORMAT)
static void test_fastformat(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        std::string r;
        // Do not know how to format hex and floating point in scientific notion
        fastformat::fmt(r, "{0} {1} {2} {3} {4} {5} {6}", i, i, ll, ll, d, d, s);
        benchmark::DoNotOptimize(r.c_str());
    }
}
#endif

static void test_tinyformat(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        std::string r = tfm::format("%d %X %lld %llX %f %e %s", i, i, ll, ll, d, d, s);
        benchmark::DoNotOptimize(r.c_str());
    }
}

BENCHMARK(test_snprintf);
BENCHMARK(test_snprintf_stackbuf);
BENCHMARK(test_sstream);
BENCHMARK(test_fmt);
BENCHMARK(test_boost_format);
#if !defined(DISABLE_FASTFORMAT)
BENCHMARK(test_fastformat);
#endif
BENCHMARK(test_tinyformat);

BENCHMARK_MAIN();
