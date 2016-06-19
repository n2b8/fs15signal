var jshint = require('gulp-jshint');
var stylish = require('jshint-stylish');
var gulp = require('gulp');

gulp.task('default', ['watch']);

gulp.task('lint', function() {
  return gulp.src(['./*.js', './js/*.js'])
    .pipe(jshint())
    .pipe(jshint.reporter(stylish));
});

gulp.task('watch', function() {
  gulp.watch(['./*.js', './js/*.js'], ['lint']);
});