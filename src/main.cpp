// (c) 2019 by Paul Wichern
// This code is licensed under MIT license (see LICENSE.txt for details)

#include "LeuchtAPI.h"

#include <iostream>

using namespace Pistache;

static const char* S_IndexHTML = R"V0G0N(
        <!doctype html>
        <html lang=\"en\">
        <head>
            <meta charset="utf-8">
            <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
            <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
            <title>Leucht</title>
        </head>
        <body>
            <div class="container">
                <h3>Leucht</h3>
                <div id="errors"></div>
                <div class="list-group" id="features"></div>
            </div>
            <script src="http://code.jquery.com/jquery-3.4.1.min.js" integrity="sha256-CSXorXvZcTkaix6Yvo6HppcZGetbYMGWSFlBw8HfCJo="crossorigin="anonymous"></script>
            <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js" integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM" crossorigin="anonymous"></script>

            <script>
            function switch_state(state) {
                $('#errors').empty();
                $.ajax({
                    url: 'api/active/' + state,
                    method: 'POST',
                    dataType: 'text'
                }).done(function(data) {
                     $('#features').children('a').each(function() {
                         $(this).removeClass("active");
                     });
                     $('#' + data).addClass("active");
                }).fail(function(jqXHR, textStatus) {
                    $('#errors').append(`<div class="alert alert-danger" role="alert">${jqXHR.status}: ${jqXHR.responseText}</div>`);
                });
            }

            $(document).ready(function() {
                // Get all features.
                $.ajax({
                    url: 'api/features',
                    method: 'GET',
                    dataType: 'json'
                }).done(function(data) {
                    for (feature of data) {
                        $('#features').append(`<a href="javascript:switch_state('${feature}')" id="${feature}" class="list-group-item list-group-item-action">${feature}</a>`);
                    }
                }).fail(function(jqXHR, textStatus) {
                    $('#errors').append(`<div class="alert alert-danger" role="alert">${textStatus}</div>`);
                });

                // Get active feature
                $.ajax({
                    url: 'api/active',
                    method: 'GET',
                    dataType: 'text'
                }).done(function(data) {
                    $('#' + data).addClass("active");
                }).fail(function(jqXHR, textStatus) {
                    $('#errors').append(`<div class="alert alert-danger" role="alert">${jqXHR.status}: ${jqXHR.responseText}</div>`);
                });
            });
            </script>
        </body>
        </html>
        )V0G0N";

int main(int argc, char* argv[])
{
    const char* hostname;

    Port port(9080);
    if (argc >= 2)
        port = std::stol(argv[1]);

    Address addr(Ipv4::any(), port);

    std::cout << "Cores = " << hardware_concurrency() << std::endl;

    LeuchtAPI leucht(addr, S_IndexHTML, { "Default", "Animation", "Music" });

    leucht.init("Default");
    leucht.start();
}

