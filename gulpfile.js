var jshint = require('gulp-jshint');
var stylish = require('jshint-stylish');
var bump = require('gulp-bump');
var gulp = require('gulp');

gulp.task('default', ['watch']);

gulp.task('lint', function() {
  return gulp.src(['./*.js', './js/*.js'])
    .pipe(jshint())
    .pipe(jshint.reporter(stylish));
});

gulp.task('bump-major', function(){
  gulp.src('./*.json')
  .pipe(bump({type:'major'}))
  .pipe(gulp.dest('./'));
});

gulp.task('bump-minor', function(){
  gulp.src('./*.json')
  .pipe(bump({type:'minor'}))
  .pipe(gulp.dest('./'));
});

gulp.task('bump-patch', function(){
  gulp.src('./*.json')
  .pipe(bump({type:'patch'}))
  .pipe(gulp.dest('./'));
});

gulp.task('watch', function() {
  gulp.watch(['./*.js', './js/*.js'], ['lint']);
});