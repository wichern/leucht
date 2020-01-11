#ifndef __LEUCHT_RESOURCES_INDEXHTML_H__
#define __LEUCHT_RESOURCES_INDEXHTML_H__

namespace resource {

static const char* const IndexHTML = R"HTML(<!doctype html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
    <link href="https://stackpath.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" rel="stylesheet" integrity="sha384-wvfXpqpZZVQGK6TAh5PVlGOfQNHSoD2xbE+QkPxCAFlNEevoEH3Sl0sibVcOQVnN" crossorigin="anonymous">
    <title>Leucht</title>
</head>
<body>
    <nav class="navbar navbar-expand-sm navbar-light bg-light">
        <a class="navbar-brand" href="#">Leucht</a>
    </nav>

    <div id="errors"></div>

    <div class="container mt-2">
        <div class="list-group" id="apps"></div>
    </div>

    <div class="row justify-content-center mt-5">
         <table class="table table-borderless" style="width:0px">
              <tr>
                   <td style="margin:0px; padding:0px"></td>
                   <td style="margin:0px; padding:0px"><button class="btn btn-dark btn-lg btn-block m-2" onclick="button_pressed(0)"><i class="fa fa-arrow-up"></i></button></td>
                   <td style="margin:0px; padding:0px"></td>
              </tr>
              <tr>
                   <td style="margin:0px; padding:0px"><button class="btn btn-dark btn-lg btn-block m-2" onclick="button_pressed(1)"><i class="fa fa-arrow-left"></i></button></td>
                   <td style="margin:0px; padding:0px"></td>
                   <td style="margin:0px; padding:0px"><button class="btn btn-dark btn-lg btn-block m-2" onclick="button_pressed(2)"><i class="fa fa-arrow-right"></i></button></td>
              </tr>
              <tr>
                   <td style="margin:0px; padding:0px"></td>
                   <td style="margin:0px; padding:0px"><button class="btn btn-dark btn-lg btn-block m-2" onclick="button_pressed(3)"><i class="fa fa-arrow-down"></i></button></td>
                   <td style="margin:0px; padding:0px"></td>
              </tr>
         </table>
    </div>

    <script src="http://code.jquery.com/jquery-3.4.1.min.js" integrity="sha256-CSXorXvZcTkaix6Yvo6HppcZGetbYMGWSFlBw8HfCJo="crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js" integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM" crossorigin="anonymous"></script>
    <script src="leucht.js"></script>
</body>
</html>)HTML";

}  // namespace resource

#endif  // __LEUCHT_RESOURCES_INDEXHTML_H__
