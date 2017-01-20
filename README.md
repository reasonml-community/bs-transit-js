# Transit-js Bucklescript bindings #

Make client-server communication great again.

This repo provides rudimentary bindings to transit-js with Bucklescript,
prototyped in under 15min. thanks to Bucklescript compiling at the speed of light.

Json is nice, but I want to send records and variants (among other things) straight over
the wire. Feels like a shame to lose all that information & type everything as js objects.
Since transit provides a way to encode/decode custom data, it seemed like
a good fit for encoding ml types. If this thing works out, I'll look into automating
everything with ppx.

Head over to `src/example.re` to get up & running ASAP.
