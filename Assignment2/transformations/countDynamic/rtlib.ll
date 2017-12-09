; ModuleID = 'transformations/countDynamic/rtlib.bc'
source_filename = "transformations/countDynamic/rtlib.cpp"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@counts = local_unnamed_addr global [100 x i32] zeroinitializer, align 16
@.str = private unnamed_addr constant [24 x i8] c"Opcode: %i, count: %i \0A\00", align 1

; Function Attrs: norecurse nounwind uwtable
define void @_Z9logCountsi(i32) local_unnamed_addr #0 {
  %2 = sext i32 %0 to i64
  %3 = getelementptr inbounds [100 x i32], [100 x i32]* @counts, i64 0, i64 %2
  %4 = load i32, i32* %3, align 4, !tbaa !1
  %5 = add nsw i32 %4, 1
  store i32 %5, i32* %3, align 4, !tbaa !1
  ret void
}

; Function Attrs: nounwind uwtable
define void @_Z11printCountsi(i32) local_unnamed_addr #1 {
  %2 = sext i32 %0 to i64
  %3 = getelementptr inbounds [100 x i32], [100 x i32]* @counts, i64 0, i64 %2
  %4 = load i32, i32* %3, align 4, !tbaa !1
  %5 = add nsw i32 %4, 1
  store i32 %5, i32* %3, align 4, !tbaa !1
  br label %7

; <label>:6:                                      ; preds = %15
  ret void

; <label>:7:                                      ; preds = %15, %1
  %8 = phi i64 [ 0, %1 ], [ %16, %15 ]
  %9 = getelementptr inbounds [100 x i32], [100 x i32]* @counts, i64 0, i64 %8
  %10 = load i32, i32* %9, align 4, !tbaa !1
  %11 = icmp sgt i32 %10, 0
  br i1 %11, label %12, label %15

; <label>:12:                                     ; preds = %7
  %13 = trunc i64 %8 to i32
  %14 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str, i64 0, i64 0), i32 %13, i32 %10)
  br label %15

; <label>:15:                                     ; preds = %7, %12
  %16 = add nuw nsw i64 %8, 1
  %17 = icmp eq i64 %16, 100
  br i1 %17, label %6, label %7
}

; Function Attrs: nounwind
declare i32 @printf(i8* nocapture readonly, ...) local_unnamed_addr #2

attributes #0 = { norecurse nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.1-6 (tags/RELEASE_401/final)"}
!1 = !{!2, !2, i64 0}
!2 = !{!"int", !3, i64 0}
!3 = !{!"omnipotent char", !4, i64 0}
!4 = !{!"Simple C++ TBAA"}
