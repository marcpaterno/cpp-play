adjust_raw_df <- function(d) {
  d |>
    tidyr::separate_wider_delim(cols=name,
                         delim="_",
                         names=c("fcn", "size")) |>
    dplyr::mutate(fcn=forcats::as_factor(fcn),
           size=as.integer(size))
}