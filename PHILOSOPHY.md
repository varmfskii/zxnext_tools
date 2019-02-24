# Philosophy

A note on programming philosophy and image formats.  These utilities
are written in the tradition of having programs that do one thing and
(try to) do it well. For this reason the idea is to have a lot of
small programs rather than a few big ones that can do everything. As
to image formats, there are a lot of image formats they have their
strengths and weaknesses. Since I have access to things like
ImageMagick and netpbm+, I see little reason to support a lot of image
formats directly. The choices I have made are pbm, pgm, and ppm (tying
directly to the ideas of netpbm+ which uses these formats as
intermediate formats). As a result most require the presence of
libnetpbm to compile/run.

My view on open source software is that if you are unsatisfied with a
piece of software, you can let the creator know about it. Don't expect
them to do anything about your concerns. They probably care, but they
have their own priorities and reasons for doing things. If your
concerns are not sufficiently addressed and you have the ability, then
fix things so they fit with your ideas.
